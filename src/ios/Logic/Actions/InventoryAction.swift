//
//  InventoryAction.swift
//  IDHand2
//
//  Copyright © 2015 N.V. Nederlandsche Apparatenfabriek "NEDAP". All rights reserved.
//

import Foundation
import ObjectiveC
import NedapIdReader


// MARK: - 
// MARK: InventoryActionDelegate protocol

/// Delegate for InventoryAction, provides callbacks to registered delegate
protocol InventoryActionDelegate: class {
    /// Called when !D Hand starts reading EPCs
    func idHandDidStartReading()

    /// Called when !D Hand stops reading EPCs
    func idHandDidStopReading()

    /// Called when !D Hand received EPC observations
    func idHandDidReceiveObservations(observations: [EpcObservation])

    /// Called when !D Hand encounters an error
    func idHandDidEncounterErrorWhileInventory(error: NSError)
}


// MARK: - 
// MARK: InventoryAction class

/// Responsible for connecting the !D Hand to the InventorySession
class InventoryAction : NSObject, Action, IDRDeviceListener {

    // MARK: -
    // MARK: Variables

    /// The !D Hand object; responsible for device interaction
    var idHand : IdHand

    /// Optional delegate for callbacks regarding to !D Hand behavior
    weak var delegate: InventoryActionDelegate?

    /// The !D Hand settings
    private var settings : IdHandSettings

    /// Bool that states if we have started this action
    private var started = false
    
    /// Bool that states if we are currently reading
    private var reading = false
    
    /// Last time we gave the user feedback via the !D Hand
    private var lastFeedbackTime : NSDate = NSDate()

    /// !D Hand feedback rate limiter interval
    private let BeepTimeInterval = 0.1


    // MARK: -
    // MARK: Action methods

    func prepare() {
        started = false
            
        // Register for reader callbacks
        idHand.device.addListener(self)
    }
    
    
    func start() {
        started = true
    }
    
    
    func stop() {
        // Notify user that the !D Hand has stopped reading
        if started && reading {
            idHand.feedback(IdHandFeedback.Alert)
        }

        // Stop the !D Hand
        sendStopCommand()

        started = false
    }
    
    
    func cleanup() {
        // Stop reading
        stop()
        
        // Unregister for callbacks
        idHand.device.removeListener(self)
    }
    
    
    // MARK: - 
    // MARK: InventoryAction methods
    
    /// Initialize an InventoryAction with an IdHand
    init(idHand: IdHand, settings : IdHandSettings) {
        self.idHand = idHand
        self.settings = settings
    }

    
    /// Reader feedback for X observations
    func feedbackForEpcObservations(numberOfEpcs : Int) {
        // Only notify user of observations when started and reading
        if started && reading && numberOfEpcs > 0 {
            
            // Do not overload the !D Hand with too many feedback requests, it 
            // will not be able to process them all
            let date = NSDate()
            let timeSinceLastFeedback = date.timeIntervalSinceDate(lastFeedbackTime)
            
            // When feedback was given more than BeepTimeInterval ago
            if timeSinceLastFeedback > BeepTimeInterval {
                self.lastFeedbackTime = date
                idHand.feedback(IdHandFeedback.NotifySubtle)
            }
        }
    }
    
    
    /// Notifies session of observed EPCs
    private func processObservations(observations : Array<EpcObservation>) {
        // Send the observations to the delegate, which will process them further
        delegate?.idHandDidReceiveObservations(observations)
    }
    
    
    // MARK: - 
    // MARK: !D Hand commands
    
    /// Start reading. Will ignore command when already reading
    func sendStartCommand() {
        if started && !reading {
            
            reading = true

            // Send smart inventory command (no need to manage antenna mismatch errors)
            idHand.device.send(IDRStartInventorySmartPacket())

            // Start blinking the !D Hand LED
            idHand.light(IdHandLight.Blinking)

            // Notify the delegate
            delegate?.idHandDidStartReading()
        }
    }
    

    /// Stop inventory. Will ignore command when not reading
    func sendStopCommand() {
        if started && reading {
            reading = false

            // Stop inventory
            idHand.device.send(IDRStopInventoryPacket())

            // Stop the !D Hand LED from blinking
            idHand.light(IdHandLight.On)
            
            // Notify the delegate
            delegate?.idHandDidStopReading()
        }
    }
    
    
    // MARK: -
    // MARK: !D Hand delegate methods
    
    func device(device: IDRDevice, receivedButtonEventPacket packet: IDRButtonEventPacket) {
        // When the button was pressed and released
        if packet.eventType == .Up {
            
            // When we are reading, stop
            if started && reading {
                // Notify user that the !D Hand has stopped reading
                idHand.feedback(IdHandFeedback.Alert)
                
                // Send stop command to the !D Hand
                self.sendStopCommand()
                
            } else {
                // Send read command to the !D Hand
                self.sendStartCommand()
            }
        }
    }
    
    
    func device(device: IDRDevice, receivedInventoryObservationPacket packet: IDRInventoryObservationPacket) {
        // Process observations in this read cycle when we have started
        if started && reading {
            
            // Array of EPC observations that we have received this read cycle
            var epcObservations = [EpcObservation]()
            
            // Loop incoming IDRObservation objects and create our own observations
            for observation in packet.observations {
                let epcObservation = EpcObservation(hex: observation.epcAsHexString, rssi: observation.rssi, count: 1)
                epcObservations.append(epcObservation)
            }
            
            // Process the received observations
            self.processObservations(epcObservations)
        }
    }
    

    func device(device: IDRDevice, receivedErrorPacket packet: IDRErrorPacket) {
        if started && reading {
            sendStopCommand()

            // Notify user that !D Hand failed to do inventory
            idHand.feedback(IdHandFeedback.Failure)

            // An UnknownCommand error is most likely to occur if the !D Hand is running old firmware
            if packet.isProtocolError(.UnknownCommand) {
                let error : NSError = NSError(domain: "idHandErrorInventory", code: 1, userInfo: ["reason" : "Your !D Hand does not have the latest firmware installed. Please update the firmware first"])
                delegate?.idHandDidEncounterErrorWhileInventory(error)

            // Unexpected errors
            } else {
                let error : NSError = NSError(domain: "idHandErrorInventory", code: 0, userInfo: ["reason" : "Unhandled error: \(packet.toString())"])
                delegate?.idHandDidEncounterErrorWhileInventory(error)

                print("InventoryAction: Received unhandled error: \(packet.toString())")
            }
        }
    }
}
