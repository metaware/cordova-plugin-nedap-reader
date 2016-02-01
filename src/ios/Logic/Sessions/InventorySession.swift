//
//  InventorySession.swift
//  IDHand2
//
//  Copyright © 2015 N.V. Nederlandsche Apparatenfabriek "NEDAP". All rights reserved.
//

import Foundation


// MARK: - 
// MARK: InventorySessionDelegate protocol

/// Delegate protocol to InventorySession. Delegate will receive callbacks / notifications 
/// for various events
protocol InventorySessionDelegate: class {
    /// Callback when !D Hand selected
    func inventoryIdHandIsSelected()

    /// Callback when !D Hand deselected
    func inventoryIdHandIsDeselected()

    /// Callback when !D Hand started reading
    func inventoryIdHandDidStartReading()
    
    /// Callback when !D Hand stopped reading
    func inventoryIdHandDidStopReading()

    /// Called when the battery level of the selected !D Hand has changed
    func inventoryIdHandBatteryLevelUpdate(idHand : IdHand, batteryPercentage : Int)

    /// Callback when !D Hand did receive a battery warning
    func inventoryIdHandBatteryWarning(idHand : IdHand, batteryPercentage : Int)

    /// Callback when error was encountered
    func inventoryDidEncounterError(error : NSError)
}


// MARK: -
// MARK: InventorySession class

/// Responsible for the inventory session; connects the !D Hand to the UI 
class InventorySession : InventoryActionDelegate, IdHandConnectorObserver {

    /// Delegate which will receive callbacks from this session
    weak var delegate : InventorySessionDelegate?

    /// Responsible for connecting !D Hands
    private var idHandConnector : IdHandConnector
    
    /// Responsible for counting observations
    private var observationCounter : ObservationCounter
    
    /// Responsible for linking the session to the action
    private var inventoryAction : InventoryAction?

    /// Responsible for keeping track of !D Hand settings
    private var idHandSettings : IdHandSettings


    init(idHandConnector : IdHandConnector, idHandSettings : IdHandSettings, observationCounter: ObservationCounter) {
        // Set connector, observationCounter and idHandSettings
        self.idHandConnector = idHandConnector
        self.idHandSettings = idHandSettings
        self.observationCounter = observationCounter

        // Set connector delegate
        idHandConnector.addObserver(self)

        // Load inventory action
        loadInventoryAction()
    }

    
    deinit {
        idHandConnector.removeObserver(self)
        unloadInventoryAction()
    }


    /// Initializes inventory action, sets self as delegate and prepares action
    private func loadInventoryAction() {
        if let selectedIdHand = idHandConnector.selectedIdHand {
            inventoryAction = InventoryAction(idHand: selectedIdHand, settings:idHandSettings)
            inventoryAction?.delegate = self
        }

        // Prepare the action 
        prepare()
    }


    /// Cleanup inventory action
    private func unloadInventoryAction() {
        // Stop
        inventoryAction?.stop()

        // Clear the action
        inventoryAction?.delegate = nil
        inventoryAction?.cleanup()
        inventoryAction = nil
    }


    // MARK: - 
    // MARK: Session methods
    
    /// Prepare the inventory session
    func prepare() {
        inventoryAction?.prepare()
    }
    
    
    /// Start the inventory session
    func start() {
        inventoryAction?.start()
    }
    
    
    /// Stop the inventory session
    func stop() {
        inventoryAction?.stop()
    }
    

    /// Clean-up the inventory session
    func cleanup() {
        inventoryAction?.cleanup()
    }


    /// Count of all unique observations
    func uniqueCount() -> Int {
        return observationCounter.uniqueCount()
    }


    /// Count of all observations, regardless of their uniqueness
    func totalCount() -> Int {
        return observationCounter.totalCount()
    }


    /// All observed EPCs
    func epcObservations() -> [EpcObservation] {
        return observationCounter.epcObservations()
    }


    // MARK: - 
    // MARK: IdHandConnectorDelegate methods

    func idHandDidConnect(idHand: IdHand) {
        // Do nothing, we only want to work with the selected !D Hand
    }


    func idHandDidDisconnect(idHand: IdHand) {
        // Do nothing, we only want to work with the selected !D Hand
    }


    func idHandIsSelected(idHand: IdHand) {
        loadInventoryAction()

        // Notify the delegate
        delegate?.inventoryIdHandIsSelected()
    }


    func idHandIsDeselected() {
        unloadInventoryAction()

        // Notify the delegate
        delegate?.inventoryIdHandIsDeselected()
    }


    func idHandSettingsUpdated() {
        // We don't handle this here, only when selecting an !D Hand
    }


    func idHandBatteryLevelUpdate(idHand : IdHand, batteryPercentage : Int) {
        delegate?.inventoryIdHandBatteryLevelUpdate(idHand, batteryPercentage: batteryPercentage)
    }


    func idHandBatteryWarning(idHand : IdHand, batteryPercentage : Int) {
        delegate?.inventoryIdHandBatteryWarning(idHand, batteryPercentage: batteryPercentage)
    }
    

    // MARK: -
    // MARK: InventoryActionDelegate methods
    
    func idHandDidReceiveObservations(observations : [EpcObservation]) {
        // Add observed EPCs
        let newObservationCount = self.observationCounter.addEpcObservations(observations)

        // Give user feedback for only newly observed EPCs
        self.inventoryAction?.feedbackForEpcObservations(newObservationCount)
    }


    func idHandDidStartReading() {
        delegate?.inventoryIdHandDidStartReading()
    }
    
    
    func idHandDidStopReading() {
        delegate?.inventoryIdHandDidStopReading()
    }
    
    
    func idHandDidEncounterErrorWhileInventory(error: NSError) {
        delegate?.inventoryDidEncounterError(error)
    }
}
