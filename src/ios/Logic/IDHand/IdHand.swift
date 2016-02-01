//
//  IdHand.swift
//  IDHand2
//
//  Copyright © 2015 N.V. Nederlandsche Apparatenfabriek "NEDAP". All rights reserved.
//

import Foundation
import NedapIdReader


// MARK: - 
// MARK: IdHand enums & constants

/// Enumerates the session types for the RFID session
enum IdHandRFIDSessionType : String {
    case Session0 = "Session 0"
    case Session1 = "Session 1"
    case Session2 = "Session 2"
    case Session3 = "Session 3"
}


/// Enumerates the possible RFID target choices
enum IdHandRFIDTarget : String {
    case TargetA = "Target A"
    case TargetB = "Target B"
    case Both    = "Both"
}


/// Enumerates the possible RFID Select statements
enum IdHandRFIDSelect : String {
    case Any        = "Any"
    case Asserted   = "Asserted"
    case Deasserted = "Deasserted"
}


/// Enumerates types of feedback that the !D Hand is capable of
enum IdHandFeedback {
    case Notify
    case NotifySubtle
    case Success
    case Failure
    case Alert
    case Connect
    case Disconnect
    case BatteryLow
}


/// Enumerates the charging statuses; including USB vs wireless charging
enum IdHandChargingStatus {
    case NotCharging
    case ChargingWireless
    case ChargingUsb
}


/// Enumerates !D Hand button light statuses
enum IdHandLight {
    case On
    case Off
    case Blinking
}


struct IdHandOutputPower {
    let min : Int
    let max : Int
}


// MARK: -
// MARK: IdHand class

/// Represents connected !D Hand, wraps EAAccessory and implements IDRReader
class IdHand : NSObject, IDRDeviceListener {

    // MARK: -
    // MARK: Variables

    /// The device with which we exchange communication packets
    let device : IDRDevice

    /// The current EAAccessory instance
    var accessory : EAAccessory?

    /// !D Hand name
    var name : String?

    /// !D Hand serial number
    var serial : String?

    /// Array of supported regulations for this !D Hand
    var supportedRegulations : [IDRRegulationWrapper]?

    /// Minimum and maximum output power as retrieved from the !D Hand
    private(set) var outputPowerBoundaries : IdHandOutputPower?

    /// Callback after device initialization is completed
    private var initCallback : (() -> ())?

    /// Callback after device regulation is set
    private var regulationCallback : (() -> ())?

    /// Callback for when version packet response is received
    private var versionCallback : ((version: Int) -> ())?

    /// Callback for when power state packet response is received
    private var powerStateCallback: ((batteryLevel: Int, batteryHealth: Int, chargingStatus : IdHandChargingStatus) -> ())?

    /// State of regulation-related calls (used to determine if the receivedRegulation callback was for an IDRGetRegulation or an IDRSetRegulation)
    private var isIDRGetRegulationCallbackExpected : Bool = false

    /// State of outputpower-related calls (used to determine if the receivedOutputPower callback was for an IDRGetOutputPower or an IDRSetOutputPower)
    private var isIDRGetOutputPowerCallbackExpected : Bool = false


    // MARK: -
    // MARK: IdHand methods

    /// Initializes !D Hand with EAAccessory
    init(accessory: EAAccessory) {
        self.accessory = accessory
        device = IDRAccessoryDevice(accessory: accessory)
        name = accessory.name
        serial = accessory.serialNumber

        // Default init values, will be overruled as soon as the !D Hand connects
        sessionType = IdHandRFIDSessionType.Session1
        target = IdHandRFIDTarget.TargetA
        select = IdHandRFIDSelect.Any

        super.init()
    }


    // MARK: -
    // MARK: Initialization steps

    /// Initialize !D Hand, set reader and connect
    func initialize(whenDone: () -> ()) {
        initCallback = whenDone

        print("Initializing !D Hand")
        device.addListener(self)
        device.connect()
    }


    // Cleanly disconnect !D Hand
    func disconnect() {
        print("!D Hand disconnecting")
        device.disconnect()
        device.removeListener(self)
    }


    /// Sets !D Hand to default state when connects; retrieves regulations
    private func initializeConnectedDevice() {
        print("!D Hand connected, setting up")

        // Switch on the light
        light(IdHandLight.On)

        // Get supported regulations
        retrieveSupportedRegulations()
    }


    /// After !D Hand has connected and regulations have been acquired, initialize the !D Hand
    private func runInitCallback() {
        print("!D Hand connected and ready")

        initCallback?()
        initCallback = nil
    }

    func toDict() -> NSDictionary {
      return [
        "name": self.deviceName(),
        "serial": self.serialNumber(),
        "manufacturer": self.manufacturer()
      ]
    }


    // MARK: -
    // MARK: Device settings

    /// Regulation of the !D Hand; required to be set to conform to local RFID laws
    private var _regulation : IDRRegulationWrapper?
    func getRegulation() -> IDRRegulationWrapper? {
        return _regulation
    }
    func setRegulation(newRegulation : IDRRegulationWrapper?, whenDone: () -> ()) {
        regulationCallback = whenDone

        guard let newRegulation = newRegulation else {
            print("!D Hand: regulation reset to nil")
            _regulation = nil

            regulationCallback?()
            regulationCallback = nil

            return
        }

        // If the new regulation is in the list of supported regulations, accept it
        if supportsRegulation(newRegulation) {
            print("!D Hand: setting regulation to \(newRegulation.toString())")
            device.send(IDRSetRegulationPacket(regulation: newRegulation.value))
        } else {
            print("!D Hand: regulation reset because of unsupported regulation \(newRegulation.toString())")
            _regulation = nil

            regulationCallback?()
            regulationCallback = nil
        }
    }


    /// Output power of the !D Hand; can only be set between min and max output power values
    /// Defaults to maximum ouput power
    private var _outputPower : Int?
    var outputPower : Int {
        get {
            if let _outputPower = _outputPower {
                return _outputPower
            } else {
                guard let outputPowerBoundaries = outputPowerBoundaries else {
                    return 0
                }
                return outputPowerBoundaries.max
            }
        }
        set {
            guard let outputPowerBoundaries = outputPowerBoundaries else {
                print("!D Hand: cannot set output power, min & max not determined yet")
                _outputPower = nil
                return
            }

            if newValue < outputPowerBoundaries.min {
                _outputPower = outputPowerBoundaries.min
            } else if newValue > outputPowerBoundaries.max {
                _outputPower = outputPowerBoundaries.max
            } else {
                _outputPower = newValue
            }

            print("!D Hand: setting output power to \(Double(_outputPower!) / 10) dBm")
            device.send(IDRSetOutputPowerPacket(powerInTenthsOfDBm: UInt16(_outputPower!)))
        }
    }


    var sessionType : IdHandRFIDSessionType {
        didSet {
            updateReaderSession()
        }
    }


    var target : IdHandRFIDTarget {
        didSet {
            updateReaderSession()
        }
    }


    var select : IdHandRFIDSelect {
        didSet {
            updateReaderSession()
        }
    }


    func supportsRegulation(regulation: IDRRegulationWrapper?) -> Bool {
        guard let regulation = regulation else {
            return false
        }

        return supportedRegulations?.indexOf(regulation) != nil
    }


    private func updateReaderSession() {
        var idHandSession : IDRSession = IDRSession.S1
        var idHandTarget : IDRTarget = IDRTarget.A
        var idHandAutoFlip : byte = 0
        var idHandSelect : IDRSelect = IDRSelect.Any

        // Convert our sessionType enum to the internal IDR session enum
        switch sessionType {
        case .Session0:
            idHandSession = IDRSession.S0
        case .Session1:
            idHandSession = IDRSession.S1
        case .Session2:
            idHandSession = IDRSession.S2
        case .Session3:
            idHandSession = IDRSession.S3
        }

        // Convert our target enum to the internal IDR target enum
        // Also sets the autoflip byte
        switch target {
        case .TargetA:
            idHandTarget = IDRTarget.A
            idHandAutoFlip = 0
        case .TargetB:
            idHandTarget = IDRTarget.B
            idHandAutoFlip = 0
        case .Both:
            idHandTarget = IDRTarget.A
            idHandAutoFlip = 1
        }

        // Convert our select enum to the internal IDR select enum
        switch select {
        case .Any:
            idHandSelect = IDRSelect.Any
        case .Asserted:
            idHandSelect = IDRSelect.Asserted
        case .Deasserted:
            idHandSelect = IDRSelect.Deasserted
        }

        device.send(IDRSetEpcGen2SessionPacket(session: idHandSession, target: idHandTarget, select: idHandSelect, autoFlip: idHandAutoFlip))
    }


    // MARK: -
    // MARK: Accessory info

    override var description : String {
        return accessory?.name ?? "Unknown reader"
    }


    /// Returns the connection state of the !D Hand
    func connected() -> Bool {
        if let accessory = accessory {
            return accessory.connected
        }

        return false
    }


    /// Returns the full name of the !D Hand
    func deviceName() -> String {
        return accessory?.name ?? ""
    }


    /// Returns the model number of the !D Hand
    func modelNumber() -> String {
        return accessory?.modelNumber ?? ""

    }


    /// Returns the firmware version of the !D Hand
    func firmwareVersion() -> String {
        return accessory?.firmwareRevision ?? ""

    }
    

    /// Returns the hardware revision of the !D Hand
    func hardwareVersion() -> String {
        return accessory?.hardwareRevision ?? ""

    }


    /// Returns the serial number of the !D Hand
    func serialNumber() -> String {
        return accessory?.serialNumber ?? ""

    }


    /// Returns the manufacturer name of the !D Hand
    func manufacturer() -> String {
        return accessory?.manufacturer ?? ""

    }
    

    /// Returns the currently selected regulation on the !D Hand
    func regulationName() -> String {
        return _regulation?.toString() ?? ""
    }


    // MARK: -
    // MARK: Device commands

    /// Resets !D Hand and sets current regulation
    func reset() {
        device.send(IDRResetPacket())

        if let _regulation = _regulation {
            device.send(IDRSetRegulationPacket(regulation: _regulation.value))
        } else {
            device.send(IDRSetRegulationPacket(regulation: IDRRegulation.NoneSelected))
        }
    }


    /// Retrieves regulation
    func retrieveSupportedRegulations() {
        print("!D Hand: retrieving supported regulations")

        // Keep track of outgoing IDRxxxRegulation calls, so we can match it with the callback
        isIDRGetRegulationCallbackExpected = true

        device.send(IDRGetRegulationPacket())
    }


    /// Retrieves regulation
    func retrieveSupportedOutputPower() {
        print("!D Hand: retrieving supported min & max output power")

        // Keep track of outgoing IDRxxxOutputPower calls, so we can match it with the callback
        isIDRGetOutputPowerCallbackExpected = true

        device.send(IDRGetOutputPowerPacket())
    }


    /// Retrieves versions and executes callback when done
    func retrieveVersion(whenDone: (version: Int) -> ()) {
        versionCallback = whenDone
        device.send(IDRGetVersionPacket())
    }


    /// Retrieves power state and executes callback when done
    func retrievePowerState(whenDone: (batteryLevel: Int, batteryHealth: Int, chargingStatus : IdHandChargingStatus) -> ()) {
        powerStateCallback = whenDone
        device.send(IDRGetPowerStatePacket())
    }

    
    /// Switches LED light mode
    func light(lightMode: IdHandLight) {
        switch lightMode {
        case .On:
            device.send(IDRSetUserLedModePacket(mode: IDRLedMode.On))
        case .Off:
            device.send(IDRSetUserLedModePacket(mode: IDRLedMode.Off))
        case .Blinking:
            device.send(IDRSetUserLedModePacket(mode: IDRLedMode.Blinking))
        }
    }
    

    /// Provides !D Hand user feedback
    func feedback(feedbackType: IdHandFeedback) {
        switch feedbackType {
        case .Notify:
            device.send(IDRUserFeedbackPacket(vibration: IDRVibrationPattern.WeakSingle, speaker: IDRSpeakerSound.Notify))
        case .NotifySubtle:
            device.send(IDRUserFeedbackPacket(vibration: IDRVibrationPattern.WeakSingle, speaker: IDRSpeakerSound.NotifySubtle))
        case .Success:
            device.send(IDRUserFeedbackPacket(vibration: IDRVibrationPattern.StrongDouble, speaker: IDRSpeakerSound.Success))
        case .Failure:
            device.send(IDRUserFeedbackPacket(vibration: IDRVibrationPattern.StrongTriple, speaker: IDRSpeakerSound.Failure))
        case .Alert:
            device.send(IDRUserFeedbackPacket(vibration: IDRVibrationPattern.WeakQuadruple, speaker: IDRSpeakerSound.Alert))
        case .Connect:
            device.send(IDRUserFeedbackPacket(vibration: IDRVibrationPattern.WeakTriple, speaker: IDRSpeakerSound.Connect))
        case .Disconnect:
            device.send(IDRUserFeedbackPacket(vibration: IDRVibrationPattern.WeakTriple, speaker: IDRSpeakerSound.Disconnect))
        case .BatteryLow:
            device.send(IDRUserFeedbackPacket(vibration: IDRVibrationPattern.WeakQuadruple, speaker: IDRSpeakerSound.BatteryLow))
        }
    }
    

    // MARK: -
    // MARK: Device callbacks

    func deviceConnected(device: IDRDevice) {
        initializeConnectedDevice()
    }


    func deviceDisconnected(device: IDRDevice) {
        // Nothing right now
        // It is possible to do some cleanup here when an !D Hand disconnects
    }
    
    
    func device(device: IDRDevice, receivedResetCompletedPacket packet: IDRResetCompletedPacket) {
        print("Reset completed")
        initializeConnectedDevice()
    }
    
    
    func device(device: IDRDevice, receivedRegulationPacket packet: IDRRegulationPacket) {
        // This callback is used for both IDRSetRegulation and IDRGetRegulation
        // If IDRGetRegulation was used, we want to process the supported regulations of the !D Hand
        if isIDRGetRegulationCallbackExpected {
            isIDRGetRegulationCallbackExpected = false

            // Store supported regulations
            supportedRegulations = packet.supportedRegulations
            print("!D Hand: received supported regulations")

            // This is the last step in device initialization
            runInitCallback()

        // If IDRSetRegulation was used, we need to store the current regulation and retrieve the min & max output power again
        } else {
            _regulation = IDRRegulationWrapper(value: packet.regulation)
            print("!D Hand: confirmed new regulation \(_regulation!.toString())")

            // Get the supported output power in this regulation
            retrieveSupportedOutputPower()

            // The getRegulation callback should not be called here, but when requested output power arrives in receivedOutputPower
        }
    }
    

    func device(device: IDRDevice, receivedOutputPowerPacket packet: IDROutputPowerPacket) {
        // This callback is used for both IDRSetOutputPower and IDRGetOutputPower
        // If IDRGetOutputPower was used, we want to process the supported output power and run some callbacks
        if isIDRGetOutputPowerCallbackExpected {
            isIDRGetOutputPowerCallbackExpected = false

            // Store minimum allowed output power
            let currentOutputPowerMin = Int(packet.minimumOutputPower)
            let currentOutputPowerMax = Int(packet.maximumOutputPower)
            outputPowerBoundaries = IdHandOutputPower(min: currentOutputPowerMin, max: currentOutputPowerMax)
            print("!D Hand: received supported min (\(Double(currentOutputPowerMin) / 10) dBm) & max (\(Double(currentOutputPowerMax) / 10) dBm) output power")

            // Check current output power against new min/max values
            if _outputPower < outputPowerBoundaries!.min {
                _outputPower = outputPowerBoundaries!.min
            } else if _outputPower > outputPowerBoundaries!.max {
                _outputPower = outputPowerBoundaries!.max
            }

            // Run the regulation callback
            // The getRegulation callback is called here because after retrieving a regulation, we also need an update on the output power values.
            // When these values arrive, we consider the regulation call to be finished, and we need to run the callback
            regulationCallback?()
            regulationCallback = nil

        // If IDRSetOutputPower was used, we only log the new output power to the console
        } else {
            print("!D Hand: confirmed new output power: \(Double(packet.outputPower) / 10) dBm")
        }
    }

    
    func device(device: IDRDevice, receivedVersionPacket packet: IDRVersionPacket) {
        if let versionCallback = versionCallback {
            let firmware = Int(packet.softwareVersion)
            versionCallback(version: firmware)
        }
        versionCallback = nil
    }


    func device(device: IDRDevice, receivedPowerStatePacket packet: IDRPowerStatePacket) {
        if let powerStateCallback = powerStateCallback {
            let batteryLevel = Int(packet.batteryLevel)
            let batteryHealth = Int(packet.batteryHealth)

            var chargingStatus : IdHandChargingStatus = IdHandChargingStatus.NotCharging
            if packet.powerSource == IDRPowerSource.USB {
                chargingStatus = IdHandChargingStatus.ChargingUsb
            } else if packet.powerSource == IDRPowerSource.Wireless {
                chargingStatus = IdHandChargingStatus.ChargingWireless
            }

            powerStateCallback(batteryLevel: batteryLevel, batteryHealth: batteryHealth, chargingStatus: chargingStatus)
        }
        powerStateCallback = nil
    }


    func device(device: IDRDevice, receivedErrorPacket packet: IDRErrorPacket) {
        if packet.isConfigurationError(.NoRegulationSelected) {
            print("IdHand: No regulation selected; please configure a regulation first!")
            _regulation = nil

            // Run the regulation callback
            regulationCallback?()
            regulationCallback = nil
        } else {
            print("!D Hand received error: \(packet.toString())")
        }
    }
    
    
    func device(device: IDRDevice, parsingFailedWithError error: NSError) {
        print("IdHand: Error occurred in API: \(error.localizedDescription)")
    }
    
}
