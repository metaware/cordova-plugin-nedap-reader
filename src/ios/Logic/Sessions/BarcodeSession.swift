//
//  BarcodeSession.swift
//  IDHand2
//
//  Copyright © 2015 N.V. Nederlandsche Apparatenfabriek "NEDAP". All rights reserved.
//

import Foundation


// MARK: -
// MARK: BarcodeSessionDelegate protocol

/// Delegate protocol to BarcodeSession. Delegate will receive callbacks / notifications
/// for various events
protocol BarcodeSessionDelegate: class {
    /// Callback when !D Hand selected
    func barcodeIdHandIsSelected()

    /// Callback when !D Hand deselected
    func barcodeIdHandIsDeselected()

    /// Callback when !D Hand started reading
    func barcodeIdHandDidStartReading()
    
    /// Callback when !D Hand stopped reading
    func barcodeIdHandDidStopReading()
    
    /// Callback when !D Hand did read one or more tag(s)
    func barcodeIdHandDidRead()

    /// Callback when !D Hand did read one or more tag(s)
    func barcodeIdHandReadFailed(errorMessage: String)

    /// Callback when !D Hand did receive a battery warning
    func barcodeIdHandBatteryWarning(idHand : IdHand, batteryPercentage : Int)

    /// Callback when error was encountered
    func barcodeDidEncounterError(error : NSError)
}


// MARK: -
// MARK: BarcodeSession class

/// Responsible for the barcode session; connects the !D Hand to the UI
class BarcodeSession : BarcodeActionDelegate, IdHandConnectorObserver {
    
    /// Delegate which will receive callbacks from this session
    weak var delegate : BarcodeSessionDelegate?
    
    /// Responsible for connecting !D Hands
    private var idHandConnector : IdHandConnector
    
    /// Responsible for linking the session to the action
    private var barcodeAction : BarcodeAction?

    /// The observed barcode
    private var observedBarcode : ObservedBarcode?
    
    
    // MARK: -
    // MARK: Init and de-init
    
    init(idHandConnector : IdHandConnector) {
        // Set connector
        self.idHandConnector = idHandConnector

        // Load barcode action
        loadBarcodeAction()

        // Set connector delegate
        idHandConnector.addObserver(self)
    }
    
    
    deinit {
        idHandConnector.removeObserver(self)
        unloadBarcodeAction()
    }


    /// Initializes inventory action, sets self as delegate and prepares action
    private func loadBarcodeAction() {
        if let selectedIdHand = idHandConnector.selectedIdHand {
            barcodeAction = BarcodeAction(idHand: selectedIdHand)
            barcodeAction?.delegate = self
        }

        // Prepare the action
        prepare()
    }


    /// Cleanup inventory action
    private func unloadBarcodeAction() {
        // Stop
        barcodeAction?.stop()

        // Clear the action
        barcodeAction?.delegate = nil
        barcodeAction?.cleanup()
        barcodeAction = nil
    }

    
    // MARK: -
    // MARK: Getters for barcode values

    /// Returns the observed barcode
    func barcode() -> String? {
        return observedBarcode?.barcodeValue
    }


    /// Returns the type of the observed barcode
    func barcodeType() -> String? {
        return observedBarcode?.barcodeType
    }
    
    
    // MARK: -
    // MARK: Session methods
    
    /// Prepare the barcode session
    func prepare() {
        barcodeAction?.prepare()
    }
    
    
    /// Start the barcode session
    func start() {
        barcodeAction?.start()
    }
    
    
    /// Stop the barcode session
    func stop() {
        barcodeAction?.stop()
    }
    
    
    /// Clean-up the barcode session
    func cleanup() {
        barcodeAction?.cleanup()
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
        loadBarcodeAction()

        delegate?.barcodeIdHandIsSelected()
    }


    func idHandIsDeselected() {
        unloadBarcodeAction()

        delegate?.barcodeIdHandIsDeselected()
    }


    func idHandSettingsUpdated() {
        // We don't handle this here, only when selecting an !D Hand
    }


    func idHandBatteryLevelUpdate(idHand : IdHand, batteryPercentage : Int) {
        // Not used here
    }


    func idHandBatteryWarning(idHand : IdHand, batteryPercentage : Int) {
        delegate?.barcodeIdHandBatteryWarning(idHand, batteryPercentage: batteryPercentage)
    }


    // MARK: -
    // MARK: BarcodeActionDelegate methods

    func idHandDidStartReadingBarcode() {
        // Clear old barcode value
        self.observedBarcode = nil

        // Notify our delegate
        delegate?.barcodeIdHandDidStartReading()
    }


    func idHandDidStopReadingBarcode() {
        delegate?.barcodeIdHandDidStopReading()
    }


    func idHandDidReadBarcode(barcode: String, barcodeType: String) {
        // Persist barcode value
        self.observedBarcode = ObservedBarcode(value: barcode, type: barcodeType)
        
        // Notify our delegate
        delegate?.barcodeIdHandDidRead()
    }
    
    
    func idHandFailedToReadBarcode(reason: String) {
        delegate?.barcodeIdHandReadFailed(reason)
    }
      
    
    func idHandDidEncounterErrorWhileReadingBarcode(error: NSError) {
        delegate?.barcodeDidEncounterError(error)
    }
}
