//
//  BarcodeAction.swift
//  IDHand2
//
//  Copyright © 2015 N.V. Nederlandsche Apparatenfabriek "NEDAP". All rights reserved.
//

import Foundation
import ObjectiveC
import NedapIdReader


// MARK: -
// MARK: BarcodeActionDelegate protocol

/// Delegate for BarcodeAction, provides callbacks to registered delegate
protocol BarcodeActionDelegate: class {
    /// Called when !D Hand starts reading a barcode
    func idHandDidStartReadingBarcode()
    
    /// Called when !D Hand stops reading a barcode
    func idHandDidStopReadingBarcode()

    /// Called when !D Hand reads a barcode with type
    func idHandDidReadBarcode(barcode: String, barcodeType: String)

    /// Called when !D Hand failed to read a barcode
    func idHandFailedToReadBarcode(reason: String)

    /// Called when !D Hand encounters an error while reading a barcode
    func idHandDidEncounterErrorWhileReadingBarcode(error: NSError)
}


// MARK: -
// MARK: BarcodeAction class

/// Responsible for connecting the !D Hand to the BarcodeSession
class BarcodeAction : NSObject, Action, IDRDeviceListener {

    // MARK: -
    // MARK: Variables
    
    /// The !D Hand object; responsible for device interaction
    private var idHand : IdHand
    
    /// Bool that states if we have started this action
    private var started = false
    
    /// Bool that states if we are currently reading
    private var reading = false
    
    /// Optional delegate for callbacks regarding to !D Hand behavior
    weak var delegate: BarcodeActionDelegate?

    /// Timeout timer for barcode reading
    private var barcodeReadTimeoutTimer : NSTimer?

    /// Timeout interval in seconds
    private let BarcodeReadTimeout = 20.0 // sec

    
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
    // MARK: BarcodeAction methods
    
    /// Initialize an BarcodeAction with an IdHand
    init(idHand: IdHand) {
        self.idHand = idHand
    }
    

    /// Timed out while reading barcode. Stop reader and notify user through failure feedback
    func barcodeReadTimedOut() {
        // Notify user that !D Hand failed to read a barcode
        idHand.feedback(IdHandFeedback.Failure)

        // Notify delegate that !D Hand failed to read a barcode
        delegate?.idHandFailedToReadBarcode("Barcode reading timed out")
        
        // Stop reading barcode
        sendStopCommand()
    }

    
    // MARK: -
    // MARK: !D Hand commands
    
    /// Start reading. Will ignore command when already reading
    func sendStartCommand() {
        if started && !reading {
            reading = true
            
            // Send barcode read command to !D Hand
            idHand.device.send(IDRStartBarcodeReaderPacket())

            // Start blinking the !D Hand LED
            idHand.light(IdHandLight.Blinking)

            // Start timeout timer
            barcodeReadTimeoutTimer?.invalidate()
            barcodeReadTimeoutTimer = NSTimer.scheduledTimerWithTimeInterval(BarcodeReadTimeout, target: self, selector: "barcodeReadTimedOut", userInfo: nil, repeats: false)
        }
    }
    
    
    /// Stop reading barcode. Will ignore command when not reading
    func sendStopCommand() {
        if started && reading {
            reading = false
            
            // Stop reading
            idHand.device.send(IDRStopBarcodeReaderPacket())

            // Stop the !D Hand LED from blinking
            idHand.light(IdHandLight.On)

            // Reset timeout
            barcodeReadTimeoutTimer?.invalidate()

            // Notify delegate that we have stopped reading a barcode
            delegate?.idHandDidStopReadingBarcode()
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

    
    func device(device: IDRDevice, receivedBarcodeReaderDataPacket packet: IDRBarcodeReaderDataPacket) {
        if started && reading {
            // Stop reading
            sendStopCommand()

            // Extract barcode from packet
            var barcode : String? = NSString(data: packet.barcodeData, encoding: NSUTF8StringEncoding) as String?
            if barcode == nil {
                barcode = hexStringFromData(packet.barcodeData)
            }

            // Provide user feedback that barcode was read successfully
            idHand.feedback(IdHandFeedback.Success)

            // Notify delegate of read barcode
            delegate?.idHandDidReadBarcode(barcode!, barcodeType: packet.symbologyName)
        }
    }
    
    
    func device(device: IDRDevice, receivedBarcodeReaderStartedPacket packet: IDRBarcodeReaderStartedPacket) {
        if started && reading {
            reading = true
            
            // Notify delegate that we have started reading a barcode
            delegate?.idHandDidStartReadingBarcode()
        }
    }
    
    
    func device(device: IDRDevice, receivedBarcodeReaderStoppedPacket packet: IDRBarcodeReaderStoppedPacket) {
        if started && reading {
            reading = false
        }
    }
 
    
    func device(device: IDRDevice, receivedErrorPacket packet: IDRErrorPacket) {
        // Try to stop nicely
        if started && reading {
            sendStopCommand()

            // Notify user that !D Hand failed to read a barcode
            idHand.feedback(IdHandFeedback.Failure)

            // Barcode reader already busy
            if packet.isStateError(.BarcodeReaderBusy) {
                delegate?.idHandFailedToReadBarcode("The !D Hand is busy with another barcode reader task")
            }

            // An UnknownCommand error is most likely to occur if the !D Hand is running old firmware
            else if packet.isProtocolError(.UnknownCommand) {
                let error : NSError = NSError(domain: "idHandErrorBarcode", code: 1, userInfo: ["reason" : "Your !D Hand does not have the latest firmware installed. Please update the firmware first"])
                delegate?.idHandDidEncounterErrorWhileReadingBarcode(error)
            }

            // Unexpected errors
            else {
                let error = NSError(domain: "idHandErrorBarcode", code: 0, userInfo: ["reason" : "Unhandled error: \(packet.toString())"])
                delegate?.idHandDidEncounterErrorWhileReadingBarcode(error)

                print("BarcodeAction: Received unhandled error: \(packet.toString())")
            }
        }
    }

    // MARK: -
    // MARK: Data to HEX string

    func hexStringFromData(data: NSData) -> String {
        var bytes = [UInt8](count: data.length, repeatedValue: 0)
        data.getBytes(&bytes, length: data.length)

        let hexString = NSMutableString()
        for byte in bytes {
            hexString.appendFormat("%02x", UInt(byte))
        }

        return hexString as String
    }
}
