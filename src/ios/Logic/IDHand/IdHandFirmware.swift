//
//  IdHandFirmware.swift
//  IDHand2
//
//  Copyright © 2015 N.V. Nederlandsche Apparatenfabriek "NEDAP". All rights reserved.
//

import Foundation
import NedapIdReader


// MARK: -
// MARK: IdHandFirmwareDelegate protocol

/// Delegate protocol to IdHandFirmware. Delegate will receive callbacks / notifications
/// for firmware update progress
protocol IdHandFirmwareDelegate: class {
    /// Callback when firmware was successfully updated
    func idHandFirmwareUpdateProgress(percentage: Int)

    /// Callback when firmware was successfully updated (verified)
    func idHandFirmwareUpdateSuccess()

    /// Callback when firmware was probably updated, and the device is still rebooting
    func idHandFirmwareUpdateRebooting()

    /// Callback when firmware was not updated
    func idHandFirmwareUpdateFailed()
}


// MARK: -
// MARK: IdHandFirmware class

/// Contains some convenience functions related to the firmware binary
class IdHandFirmware : NSObject, IdHandConnectorObserver, IDRDeviceListener {

    // MARK: -
    // MARK: Configurable variables

    // Firmware details
    private let latestVersion = 65
    private let binaryFileName = "idhand-firmware-v65.bin"

    // Update settings
    private var maxPacketsInPipeline = 5
    private let maxFailures = 15


    // MARK: -
    // MARK: Variables

    /// Delegate which will receive callbacks from  settings changes
    weak var delegate : IdHandFirmwareDelegate?

    /// Responsible for connecting !D Hands
    private var idHandConnector : IdHandConnector

    /// The !D Hand object; responsible for device interaction
    var idHand : IdHand
    private var idHandSerial : String

    // Firmware update state
    private var packets = [NSData]()
    private var packetsTotalSize : Int = 0
    private var packetsTotalCRC : UInt = 0
    private var nextPacket : Int = 0
    private var lastAckedPacket : Int = -1
    private var numberOfFailures : Int = 0
    private var updateFinished = false


    // MARK: -
    // MARK: IdHandFirmware methods

    /// Initialize an BarcodeAction with an IdHand
    init(idHandConnector: IdHandConnector, idHand: IdHand) {
        self.idHand = idHand
        idHandSerial = idHand.serial!
        self.idHandConnector = idHandConnector

        super.init()

        // Pipelined firmware updates were not supported before version 62
        if Int(idHand.firmwareVersion()) < 62 {
            maxPacketsInPipeline = 1
        }

        // Set connector delegate
        idHandConnector.addObserver(self)
    }


    /// Can be called to clean up the delegate references
    func cleanup() {
        idHandConnector.removeObserver(self)
        idHand.device.removeListener(self)
    }


    /// Returns the version of the latest available firmware
    func latestFirmwareVersion() -> Int {
        return latestVersion
    }

    
    /// Checks if there is a new firmware version for the given !D Hand
    func isUpdateAvailable() -> Bool {
        let idHandFirmwareVersion = Int(idHand.firmwareVersion())
        return latestVersion > idHandFirmwareVersion
    }


    // MARK: -
    // MARK: Firmware upgrade code

    /// Returns an array with NSData packets, which contain chunks of the firmware binary
    // private func loadFirmwarePackets() -> Bool {
    //     guard let firmwareBinaryURL = NSBundle.mainBundle().URLForResource(binaryFileName, withExtension: nil) else {
    //         return false
    //     }

    //     packets.removeAll()
    //     packetsTotalSize = 0
    //     packetsTotalCRC = 0

    //     var readBuffer = [UInt8](count: 256, repeatedValue: 0)

    //     let inputStream = NSInputStream(URL: firmwareBinaryURL)
    //     inputStream?.open()

    //     while true {
    //         if let length = inputStream?.read(&readBuffer, maxLength: readBuffer.count) {
    //             if length < 1 {
    //                 break
    //             }

    //             let data = NSData(bytes: readBuffer, length: length)
    //             packets.append(data)
    //             packetsTotalSize += length
    //             packetsTotalCRC = crc32(packetsTotalCRC, UnsafePointer<UInt8>(data.bytes), UInt32(data.length))
    //         }
    //     }

    //     inputStream?.close()
        
    //     return packets.count > 0
    // }


    /// Starts the firmware update process
    // func update() {
    //     // Load firmware packets
    //     if !loadFirmwarePackets() {
    //         updateFailed()
    //         return
    //     }

    //     // Register for reader callbacks
    //     idHand.device.addListener(self)

    //     // Start by sending the first packet
    //     // Once that one is acknowledged, we can start streaming
    //     sendFirstPacket()
    // }


    private func updateDone() {
        // Mark this update as finished; two things can happen now; an error comes in, or the !D Hand disconnects/reboots/reconnects
        // When it reboots; idHandIsDeselected will be called, from which we will handle the success scenario
        updateFinished = true
    }


    private func updateFailed() {
        // Unregister for reader callbacks
        idHand.device.removeListener(self)

        // Notify delegate
        delegate?.idHandFirmwareUpdateFailed()
    }


    private func sendProgress() {
        let total = packets.count
        var progress = 0

        if total > 0 {
            let acked = lastAckedPacket + 1
            progress = Int(round((Float(acked) / Float(total)) * 100.0))
        }

        // Send progress to delegate
        delegate?.idHandFirmwareUpdateProgress(progress)
    }


    private func sendFirstPacket() {
        // Reset
        updateFinished = false
        nextPacket = 0
        lastAckedPacket = -1

        // Send reset to delegate
        sendProgress()

        // Send first packet
        sendPacket(nextPacket)
        nextPacket++
    }


    private func sendNextPackets() {
        while ((nextPacket - lastAckedPacket) <= maxPacketsInPipeline) && nextPacket < packets.count {
            sendPacket(nextPacket)
            nextPacket++
        }
    }


    private func sendPacket(packetNumber: Int) {
        // Create & send the firmware packet
        let packet = packets[packetNumber]
        let firmwarePacket = IDRStoreFirmwareBlockPacket(packetNumber: UInt16(packetNumber), data: UnsafeMutablePointer<UInt8>(packet.bytes), dataLength: UInt32(packet.length))
        idHand.device.send(firmwarePacket)

        print("Sent packet \(packetNumber)")

        // Update progress
        sendProgress()
    }


    private func sendUpgradeCommand() {
        // Create & send the upgrade packet
        let upgradePacket = IDRStartFirmwareUpgradePacket(totalSize: UInt32(packetsTotalSize), crc: UInt32(packetsTotalCRC))
        idHand.device.send(upgradePacket)

        print("Sent upgrade command")

        // We're done!
        updateDone()
    }


    private func resetProgressToBlockBoundaryAndContinue() {
        numberOfFailures++
        if numberOfFailures > maxFailures {
            print("Too many failures, cancelling update")
            updateFailed()
            return
        }

        // Jump back to the last multiple of 16 packets
        if lastAckedPacket >= 0 {
            nextPacket = 16 * Int(floor(Float(lastAckedPacket) / 16.0))
            lastAckedPacket = nextPacket - 1
        }

        print("Received error; resetting to packet \(nextPacket)")

        if nextPacket == 0 {
            sendFirstPacket()
        } else {
            sendNextPackets()
        }
    }


    // MARK: -
    // MARK: Reader callbacks

    
    func device(device: IDRDevice, receivedStoreFirmwareBlockCompletedPacket packet: IDRStoreFirmwareBlockCompletedPacket) {
        let ackedPacket = Int(packet.packetNumber)

        print("Received ACK for packet \(ackedPacket)")

        if lastAckedPacket + 1 == ackedPacket {
            lastAckedPacket++
            print("Last ACKed packet (of total \(packets.count)) is \(lastAckedPacket)")

            if lastAckedPacket == (packets.count - 1) {
                sendUpgradeCommand()
            } else {
                sendNextPackets()
            }
        }
    }


    func device(device: IDRDevice, receivedErrorPacket packet: IDRErrorPacket) {
        // Category 'Protocol'
        // Sending packets & Upgrade command: InvalidData / InvalidCrc
        if packet.isProtocolError(.InvalidData) || packet.isProtocolError(.InvalidCrc) {
            print("Warning: ProtocolCategory / InvalidData or InvalidCrc error")

            // Upgrade command
            if updateFinished {
                updateFailed()

            // Sending packets
            } else {
                resetProgressToBlockBoundaryAndContinue()
            }
        }

        // Category 'Hardware'
        // Sending packets & Upgrade command: StoreFailed
        else if packet.isHardwareError(.StoreFailed) {
            print("Warning: HardwareCategory / StoreFailed error")

            // Upgrade command
            if updateFinished {
                updateFailed()

            // Sending packets
            } else {
                resetProgressToBlockBoundaryAndContinue()
            }
        }

        // Category 'State'
        // Upgrade command: IncorrectFirmwareCrc
        else if packet.isStateError(.IncorrectFirmwareCrc) {
            print("Warning: StateCategory / IncorrectFirmwareCrc error")
            updateFailed()
        }

        // Upgrade command: IncorrectFirmwareSignature
        else if packet.isStateError(.IncorrectFirmwareSignature) {
            print("Warning: StateCategory / IncorrectFirmwareSignature error")
            updateFailed()
        }

        // Upgrade command: Busy
        else if packet.isStateError(.RfidBusy) {
            print("Warning: StateCategory / Busy error")
            updateFailed()
        }

        // Other unhandler error
        else {
            print("IdHandFirmwareUpdate: Received unhandled error: \(packet.toString())")
        }
    }
    

    // MARK: -
    // MARK: IdHandConnectorDelegate

    func idHandDidConnect(idHand: IdHand) {
        if updateFinished && idHand.serial == idHandSerial {
            self.idHand = idHand

            if isUpdateAvailable() {
                // Still the old version?!
                delegate?.idHandFirmwareUpdateFailed()
            } else {
                // Update complete!
                delegate?.idHandFirmwareUpdateSuccess()
            }
        }
    }


    func idHandDidDisconnect(idHand: IdHand) {
        if updateFinished && idHand.serial == idHandSerial {
            // Unregister for reader callbacks
            idHand.device.removeListener(self)

            // Notify delegate of success
            delegate?.idHandFirmwareUpdateRebooting()
        }
    }


    func idHandIsSelected(idHand: IdHand) {
        // Not used here
    }


    func idHandIsDeselected() {
        // Not used here
    }


    func idHandSettingsUpdated() {
        // Not used here
    }


    func idHandBatteryLevelUpdate(idHand : IdHand, batteryPercentage : Int) {
        // Not used here
    }


    func idHandBatteryWarning(idHand : IdHand, batteryPercentage : Int) {
        // Not used here
    }
}