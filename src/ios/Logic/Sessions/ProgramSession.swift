//
//  ProgramSession.swift
//  IDHand2
//
//  Copyright © 2015 N.V. Nederlandsche Apparatenfabriek "NEDAP". All rights reserved.
//

import Foundation


// MARK: -
// MARK: ProgramSessionDelegate protocol

/// Delegate protocol to ProgramSession. Delegate will receive callbacks / notifications
/// for various events
protocol ProgramSessionDelegate: class {

    /// Callback when !D Hand selected
    func programIdHandIsSelected()
    
    /// Callback when !D Hand deselected
    func programIdHandIsDeselected()
    
    /// Callback when !D Hand started programming
    func programIdHandDidStartProgramming()
    
    /// Callback when !D Hand stopped programming
    func programIdHandDidStopProgramming()
    
    /// Callback when !D Hand did program a tag
    func programIdHandDidProgram()
    
    /// Callback when !D Hand did not program a tag due to some error
    func programIdHandDidNotProgram(errorMessage: String)
    
    /// Callback when !D Hand did receive a battery warning
    func programIdHandBatteryWarning(idHand : IdHand, batteryPercentage : Int)

    /// Callback when error was encountered
    func programDidEncounterError(error : NSError)
}


// MARK: -
// MARK: ProgramSession class

class ProgramSession : ProgramActionDelegate, IdHandConnectorObserver {
    
    /// Delegate which will receive callbacks from this session
    weak var delegate : ProgramSessionDelegate?
    
    /// Responsible for connecting !D Hands
    private var idHandConnector : IdHandConnector
    
    /// Responsible for linking the session to the action
    private var programAction : ProgramAction?
    
    /// Responsible for keeping track of !D Hand settings
    private var idHandSettings : IdHandSettings

    
    init(idHandConnector : IdHandConnector, idHandSettings : IdHandSettings) {
        // Set connector and idHandSettings
        self.idHandConnector = idHandConnector
        self.idHandSettings = idHandSettings

        // Load program action
        loadProgramAction()

        // Set connector delegate
        idHandConnector.addObserver(self)
    }
    
    
    deinit {
        idHandConnector.removeObserver(self)
        unloadProgramAction()
    }
    
    
    private func loadProgramAction() {
        if let selectedIdHand = idHandConnector.selectedIdHand {
            programAction = ProgramAction(idHand: selectedIdHand, settings:idHandSettings)
            programAction?.delegate = self
        }
        
        // Prepares the action
        prepare()
    }
    
    
    private func unloadProgramAction() {
        // Stop
        programAction?.stop()
        
        // Clear the action
        programAction?.delegate = nil
        programAction?.cleanup()
        programAction = nil
    }
    

    /// Setter for the HEX value to program
    func programHex(hex: String) {
        programAction?.hex = hex
    }
    
    
    // MARK: -
    // MARK: Session methods
    
    /// Prepare the program session
    func prepare() {
        programAction?.prepare()
    }
    
    
    /// Start the program session
    func start() {
        programAction?.start()
    }
    
    
    /// Stop the program session
    func stop() {
        programAction?.stop()
    }
    
    
    /// Clean-up the program session
    func cleanup() {
        programAction?.cleanup()
    }

    
    // MARK: -
    // MARK: IdHandConnectorDelegate methods
    
    func idHandIsSelected(idHand : IdHand) {
        loadProgramAction()

        // Notify the delegate
        delegate?.programIdHandIsSelected()
    }
    
    
    func idHandIsDeselected() {
        unloadProgramAction()

        // Notify the delegate
        delegate?.programIdHandIsDeselected()
    }
    
    
    func idHandDidConnect(idHand : IdHand) {
        // Do nothing, we only want to work with the selected !D Hand
    }
    
    
    func idHandDidDisconnect(idHand : IdHand) {
        // Do nothing, we only want to work with the selected !D Hand
    }
    
    
    func idHandSettingsUpdated() {
        // We don't handle this here, only when selecting an !D Hand
    }


    func idHandBatteryLevelUpdate(idHand : IdHand, batteryPercentage : Int) {
        // Not used here
    }


    func idHandBatteryWarning(idHand : IdHand, batteryPercentage : Int) {
        delegate?.programIdHandBatteryWarning(idHand, batteryPercentage: batteryPercentage)
    }

    
    // MARK: -
    // MARK: ProgramActionDelegate methods

    func idHandDidStartProgrammingTag() {
        delegate?.programIdHandDidStartProgramming()
    }


    func idHandDidStopProgrammingTag() {
        delegate?.programIdHandDidStopProgramming()
    }


    func idHandDidProgramTag() {
        delegate?.programIdHandDidProgram()
    }
       

    func idHandFailedToProgramTag(reason: String) {
        delegate?.programIdHandDidNotProgram(reason)
    }


    func idHandDidEncounterErrorWhileProgramming(error: NSError) {
        delegate?.programDidEncounterError(error)
    }
}
