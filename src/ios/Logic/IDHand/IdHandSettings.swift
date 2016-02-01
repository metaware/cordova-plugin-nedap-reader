//
//  IdHandSettings.swift
//  IDHand2
//
//  Copyright © 2015 N.V. Nederlandsche Apparatenfabriek "NEDAP". All rights reserved.
//

import Foundation
import UIKit
import NedapIdReader


// Hardcoded to have some limits for the UI before an actual !D Hand is connected
let IdHandMinimumOutputPower : Int = 140
let IdHandMaximumOutputPower : Int = 260


// MARK: -
// MARK: Settings keys

let keyRFIDSessionType = "IdHandRFIDSessionType"
let keyRFIDTarget = "IdHandRFIDTarget"
let keyRFIDSelect = "IdHandRFIDSelect"
let keyOutputPower = "IdHandOutputPower"
let keyRegulation = "IdHandRegulation"


// MARK: -
// MARK: IdHandSettingsDelegate protocol

/// Delegate protocol to IdHandSettings. Delegate will receive callbacks / notifications
/// for setting updates
protocol IdHandSettingsDelegate: class {
    /// Callback when new settings are selected
    func settingsDidUpdate()
}


// MARK: -
// MARK: IdHandSettings class

/// Contains settings used for !D Hand
class IdHandSettings {

    // MARK: -
    // MARK: Variables

    /// Delegate which will receive callbacks from  settings changes
    weak var delegate : IdHandSettingsDelegate?


    /// RFID Session to read, default session 1
    var session : IdHandRFIDSessionType = IdHandRFIDSessionType.Session1 {
        didSet {
            settingsUpdated()
        }
    }


    /// RFID Target, default A
    var target : IdHandRFIDTarget = IdHandRFIDTarget.TargetA {
        didSet {
            settingsUpdated()
        }
    }


    /// RFID Select, default Any
    var select : IdHandRFIDSelect = IdHandRFIDSelect.Any {
        didSet {
            settingsUpdated()
        }
    }


    /// Output power, default 0
    var outputPower : Int? {
        didSet {
            settingsUpdated()
        }
    }


    /// Regulation where this !D Hand operates in
    var regulation : IDRRegulationWrapper? {
        didSet {
            settingsUpdated()
        }
    }


    /// Output power, maximum; either hardcoded or from the connected !D Hand
    var maximumOutputPower : Int {
        get {
            // Get reference to the App Delegate
            // let appDelegate = UIApplication.sharedApplication().delegate as! AppDelegate
            // return appDelegate.idHandConnector.selectedIdHand?.outputPowerBoundaries?.max ?? IdHandMaximumOutputPower
            return IdHandMaximumOutputPower;
        }
    }


    /// Output power, maximum; either hardcoded or from the connected !D Hand
    var minimumOutputPower : Int {
        get {
            // Get reference to the App Delegate
            // let appDelegate = UIApplication.sharedApplication().delegate as! AppDelegate
            // return appDelegate.idHandConnector.selectedIdHand?.outputPowerBoundaries?.min ?? IdHandMinimumOutputPower
            return IdHandMinimumOutputPower
        }
    }


    // MARK: -
    // MARK: IdHandSettings methods

    /// Loads IdHandSettings from User Defaults
    init() {
        let defaults = NSUserDefaults.standardUserDefaults()

        if defaults.objectForKey(keyRFIDSessionType) != nil { // Only if userdefaults are set
            if let sessionStringValue = defaults.stringForKey(keyRFIDSessionType) {
                session = IdHandRFIDSessionType(rawValue: sessionStringValue)!
            }
        }

        if defaults.objectForKey(keyRFIDTarget) != nil {
            if let targetStringValue = defaults.stringForKey(keyRFIDTarget) {
                target = IdHandRFIDTarget(rawValue: targetStringValue)!
            }
        }

        if defaults.objectForKey(keyRFIDSelect) != nil {
            if let selectStringValue = defaults.stringForKey(keyRFIDSelect) {
                select = IdHandRFIDSelect(rawValue: selectStringValue)!
            }
        }

        if defaults.objectForKey(keyOutputPower) != nil {
            outputPower = defaults.integerForKey(keyOutputPower)
        }

        if defaults.objectForKey(keyRegulation) != nil {
            if let regulationEnum = IDRRegulation(rawValue: UInt8(defaults.integerForKey(keyRegulation))) {
                regulation = IDRRegulationWrapper(value: regulationEnum)
            }
        }
    }


    /// Stores IdHandSettings in User Defaults
    private func settingsUpdated() {
        let defaults = NSUserDefaults.standardUserDefaults()

        // Store !DHand RFID settings and output power
        defaults.setObject(session.rawValue, forKey: keyRFIDSessionType)
        defaults.setObject(target.rawValue, forKey: keyRFIDTarget)
        defaults.setObject(select.rawValue, forKey: keyRFIDSelect)
        if let outputPower = outputPower {
            defaults.setInteger(outputPower, forKey: keyOutputPower)
        }

        // Store selected regulation
        let regulationEnumValue : UInt8 = (regulation?.value.rawValue)!
        let regulationValue : Int = Int(regulationEnumValue)
        defaults.setInteger(regulationValue, forKey: keyRegulation)
        
        defaults.synchronize()
        
        // Notify delegate
        delegate?.settingsDidUpdate()
    }
}
