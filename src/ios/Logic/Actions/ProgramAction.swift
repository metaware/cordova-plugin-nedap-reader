//
//  ProgramAction.swift
//  IDHand2
//
//  Copyright © 2015 N.V. Nederlandsche Apparatenfabriek "NEDAP". All rights reserved.
//

import Foundation
import NedapIdReader


// MARK: -
// MARK: ProgramActionDelegate protocol

/// Delegate for ProgramAction, provides callbacks to registered delegate
protocol ProgramActionDelegate: class {
    /// Called when !D Hand starts programming a tag
    func idHandDidStartProgrammingTag()

    /// Called when !D Hand stops programming a tag
    func idHandDidStopProgrammingTag()

    /// Called when !D Hand programs a tag
    func idHandDidProgramTag()

    /// Called when !D Hand failed to program a tag
    func idHandFailedToProgramTag(reason: String)

    /// Called when !D Hand encounters an error while programming a tag
    func idHandDidEncounterErrorWhileProgramming(error: NSError)
}


// MARK: -
// MARK: ProgramAction class

/// Responsible for connecting the !D Hand to the ProgramSession
class ProgramAction : NSObject, Action, IDRDeviceListener {
    
    // MARK: -
    // MARK: Variables
    
    /// The !D Hand object; responsible for device interaction
    private var idHand : IdHand
    
    /// The !D Hand settings
    private var settings : IdHandSettings
    
    /// Bool that states if we have started this action
    private var started = false
    
    /// Bool that states if we are currently writing
    private var writing = false
    
    /// Optional delegate for callbacks regarding to !D Hand behavior
    weak var delegate: ProgramActionDelegate?
    
    /// The hexadecimal value to program
    var hex : String?

    
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
        // Stop the !D Hand LED from blinking
        idHand.light(IdHandLight.On)

        started = false
    }
    
    
    func cleanup() {
        // Stop programming
        stop()
        
        // Unregister for callbacks
        idHand.device.removeListener(self)
    }
    
    
    // MARK: -
    // MARK: ProgramAction methods
    
    /// Initialize an ProgramAction with an IdHand
    init(idHand: IdHand, settings : IdHandSettings) {
        self.idHand = idHand
        self.settings = settings
    }
    
    
    // MARK: -
    // MARK: !D Hand commands
    
    /// Start writing. Will ignore command when already writing
    func sendWriteCommand() {
        if started && !writing {
            // Check if a good HEX value was provided
            guard let hex = hex else {
                delegate?.idHandFailedToProgramTag("No HEX value was provided")
                return
            }
            if hex.characters.count == 0 {
                delegate?.idHandFailedToProgramTag("No HEX value was provided")
                return
            }

            // Check if the HEX value is correct (a multiple of 2 characters)
            if hex.characters.count % 2 != 0 {
                delegate?.idHandFailedToProgramTag("An invalid HEX value was provided, it should be a multiple of 2 characters")
                return
            }

            // If everything checks out, start writing
            writing = true

            // Notify delegate that !D Hand started programming
            delegate?.idHandDidStartProgrammingTag()

            // Start blinking the !D Hand LED
            idHand.light(IdHandLight.Blinking)

            // Get bytes (in NSData) from hexadecimal string
            let epc = NSMutableData(capacity: hex.characters.count / 2)!
            for var index = hex.startIndex; index < hex.endIndex; index = index.advancedBy(2) {
                let byteString = hex.substringWithRange(Range<String.Index>(start: index, end: index.advancedBy(2)))
                var value = CUnsignedInt(byteString.withCString { strtoul($0, nil, 16) })
                epc.appendBytes(&value, length: 1)
            }

            // Send EPC write command to !D Hand
            // If tag is not locked for writing the EPC bank, we can use password = 0
            idHand.device.send(IDRProgramEpcPacket.programRawWithEpc(epc, password: 0))
        }
    }


    // MARK: -
    // MARK: !D Hand delegate methods

    func device(device: IDRDevice, receivedButtonEventPacket packet: IDRButtonEventPacket) {
        // When the button was pressed and released
        if packet.eventType == .Up {
            // Send write command to the !D Hand
            self.sendWriteCommand()
        }
    }
    

    func device(device: IDRDevice, receivedProgramEpcResultPacket packet: IDRProgramEpcResultPacket) {
        if started && writing {
            writing = false

            // Stop the !D Hand LED from blinking
            idHand.light(IdHandLight.On)

            // Notify delegate that !D Hand stopped programming
            delegate?.idHandDidStopProgrammingTag()

            switch packet.resultCode as IDRProgramEpcResultCode {
            case .Success:
                idHand.feedback(.Success)
                delegate?.idHandDidProgramTag()
            case .NoLabel:
                idHand.feedback(.Failure)
                delegate?.idHandFailedToProgramTag("No tags nearby")
            case .MultipleLabels:
                idHand.feedback(.Failure)
                delegate?.idHandFailedToProgramTag("Too many tags nearby")
            case .NoXtid:
                idHand.feedback(.Failure)
                delegate?.idHandFailedToProgramTag("Tag has no XTID")
            case .InvalidSerial:
                idHand.feedback(.Failure)
                delegate?.idHandFailedToProgramTag("Invalid serial")
            case .UnsupportedLabel:
                idHand.feedback(.Failure)
                delegate?.idHandFailedToProgramTag("Unsupported tag")
            case .WriteFailed:
                idHand.feedback(.Failure)
                delegate?.idHandFailedToProgramTag("Write failed")
            case .VerifyFailed:
                idHand.feedback(.Failure)
                delegate?.idHandFailedToProgramTag("Verify failed")
            case .LabelLost:
                idHand.feedback(.Failure)
                delegate?.idHandFailedToProgramTag("Tag lost")
            case .MemoryLocked:
                idHand.feedback(.Failure)
                delegate?.idHandFailedToProgramTag("Tag memory locked")
            case .SerialisationFailed:
                idHand.feedback(.Failure)
                delegate?.idHandFailedToProgramTag("Serialization failed")
            }
        }
    }
    

    func device(device: IDRDevice, receivedErrorPacket packet: IDRErrorPacket) {
        if started && writing {
            writing = false

            // Stop the !D Hand LED from blinking
            idHand.light(IdHandLight.On)

            // User feedback to indicate that programming failed
            idHand.feedback(.Failure)

            // Notify delegate that !D Hand stopped programming
            delegate?.idHandDidStopProgrammingTag()

            // Input validation to API was not correct, got invalid HEX value?
            if packet.isProtocolError(.InvalidData) {
                delegate?.idHandFailedToProgramTag("An invalid HEX value was provided")
            }

            // Busy with other RFID task
            else if packet.isStateError(.RfidBusy) {
                delegate?.idHandFailedToProgramTag("The !D Hand is busy with another RFID task")
            }

            // Antenna Mismatch error
            else if packet.isRfidError(.AntennaMismatch) {
                delegate?.idHandFailedToProgramTag("Antenna problem, check if the reader is near metal objects")
            }

            // An UnknownCommand error is most likely to occur if the !D Hand is running old firmware
            else if packet.isProtocolError(.UnknownCommand) {
                let error : NSError = NSError(domain: "idHandErrorProgramming", code: 1, userInfo: ["reason" : "Your !D Hand does not have the latest firmware installed. Please update the firmware first"])
                delegate?.idHandDidEncounterErrorWhileProgramming(error)
            }

            // Unexpected errors
            else {
                let error = NSError(domain: "idHandErrorProgramming", code: 0, userInfo: ["reason" : "Unhandled error: \(packet.toString())"])
                delegate?.idHandDidEncounterErrorWhileProgramming(error)
                
                print("ProgramAction: Received unhandled error: \(packet.toString())")
            }
        }
    }
}
