//
//  IdHandConnector.swift
//  IDHand2
//
//  Copyright © 2015 N.V. Nederlandsche Apparatenfabriek "NEDAP". All rights reserved.
//

import Foundation
import ExternalAccessory


let IdHandProtocol = "com.nedap.retail.idreader"


// MARK: -
// MARK: IdHandConnectorObserver protocol

/// Observer for IdHandConnector, provides callbacks to registered observer
protocol IdHandConnectorObserver : class {
    
    /// Called when !D Hand is selected
    func idHandIsSelected(idHand : IdHand)
    
    /// Called when !D Hand is deselected
    func idHandIsDeselected()
    
    /// Called when !D Hand is connected
    func idHandDidConnect(idHand : IdHand)
    
    /// Called when !D Hand disconnected
    func idHandDidDisconnect(idHand : IdHand)
    
    /// Called when !D Hand settings are updated
    func idHandSettingsUpdated()

    /// Called when the battery level of the selected !D Hand has changed
    func idHandBatteryLevelUpdate(idHand : IdHand, batteryPercentage : Int)

    /// Callback when !D Hand did receive a battery warning
    func idHandBatteryWarning(idHand : IdHand, batteryPercentage : Int)
}



// MARK: -
// MARK: IdHandConnector class

/// Responsible for detecting and connecting !D Hands
class IdHandConnector : NSObject, IdHandSettingsDelegate {

    // MARK: -
    // MARK: Variables
    
    // Keep track of all connected !D Hands
    var connectedIdHands = [IdHand]()

    /// This class can have multiple observers (stored as weak references) that will receive connection events
    private var observerSet : NSHashTable = NSHashTable.weakObjectsHashTable()

    /// settings to apply to !D Hand
    private var idHandSettings : IdHandSettings

    /// Keep track of the notification observers, so we can unregister them
    private var notificationObservers = [NSObjectProtocol]()

    /// Timer to monitor the battery status of the selected !D Hand
    private var batteryMonitorTimer : NSTimer?
    private var batteryWarnedFor20Percent = false
    private var batteryWarnedFor10Percent = false

    /// Keep track of an !D Hand that was selected but got disconnected
    /// If it reconnects, everything needs to be re-initialized because the underlying EAAccessory is a different object
    private var disconnectedLastSelectedIdHand : IdHand?


    /// Keep track of the selected !D Hand
    var selectedIdHand : IdHand? {
        didSet {
            if let selectedIdHand = selectedIdHand {
                // Apply settings to the selected !D Hand
                applySettingsToSelectedIdHand()

                // Notify the observers
                self.forEachObserver {
                    $0.idHandIsSelected(selectedIdHand)
                }

                // Clear the last disconnected !D Hand variable
                disconnectedLastSelectedIdHand = nil

                // Clear battery warnings
                batteryWarnedFor20Percent = false
                batteryWarnedFor10Percent = false

            } else {
                // Notify the observers
                self.forEachObserver {
                    $0.idHandIsDeselected()
                }
            }
        }
    }

    
    // MARK: -
    // MARK: IdHandConnector methods
    
    /// Initializes IdHandConnector with specified settings object
    init(idHandSettings: IdHandSettings) {
        // Store settings object
        self.idHandSettings = idHandSettings
        super.init()
        self.idHandSettings.delegate = self

        // Listen for accessory connects
        EAAccessoryManager.sharedAccessoryManager().registerForLocalNotifications()
        let connectObserver = NSNotificationCenter.defaultCenter().addObserverForName(EAAccessoryDidConnectNotification, object: nil, queue: nil) {
            [weak self] (notification: NSNotification) in

            if let connectedAccessory = notification.userInfo?[EAAccessoryKey] as? EAAccessory {
                self?.connect(connectedAccessory)
            }
        }
        notificationObservers.append(connectObserver)

        // Listen for accessory disconnects
        let disconnectObserver = NSNotificationCenter.defaultCenter().addObserverForName(EAAccessoryDidDisconnectNotification, object: nil, queue: nil) {
            [weak self] (notification: NSNotification) in

            if let disconnectedAccessory = notification.userInfo?[EAAccessoryKey] as? EAAccessory {
                self?.disconnect(disconnectedAccessory)
            }
        }
        notificationObservers.append(disconnectObserver)

        // Connect !D Hands that are already connected to the EAAccessory framework and will not be picked up anymore by connect notifications
        connectIdHands()

        // Start update timer
        batteryMonitorTimer = NSTimer.scheduledTimerWithTimeInterval(5.0, target: self, selector: "checkBattery", userInfo: nil, repeats: true)
    }


    /// Cleanup IdHandConnector
    deinit {
        batteryMonitorTimer?.invalidate()

        // Remove all listeners
        for observer in notificationObservers {
            NSNotificationCenter.defaultCenter().removeObserver(observer)
        }
    }


    /// Add an observer to the current observer set
    func addObserver(observerObject : IdHandConnectorObserver) {
        observerSet.addObject(observerObject)
    }


    /// Add an observer to the current observer set
    func removeObserver(observerObject : IdHandConnectorObserver) {
        observerSet.removeObject(observerObject)
    }
    
    
    /// Perform an action with each observer
    private func forEachObserver(codeBlock : (IdHandConnectorObserver) -> Void) {
        for observerObject in observerSet.allObjects {
            if let observer = observerObject as? IdHandConnectorObserver {
                codeBlock(observer)
            }
        }
    }


    /// Checks battery status of selected !D Hand (if any)
    func checkBattery() {
        guard let selectedIdHand = selectedIdHand else {
            return
        }

        selectedIdHand.retrievePowerState({ (batteryLevel, batteryHealth, chargingStatus) -> () in
            // Send battery status to observers
            self.forEachObserver {
                $0.idHandBatteryLevelUpdate(selectedIdHand, batteryPercentage: batteryLevel)
            }

            // Check if battery warning should be issued
            var warn = false
            if batteryLevel < 10 && !self.batteryWarnedFor10Percent {
                warn = true
                self.batteryWarnedFor10Percent = true
                self.batteryWarnedFor20Percent = true
            } else if batteryLevel < 20 && !self.batteryWarnedFor20Percent {
                warn = true
                self.batteryWarnedFor10Percent = false
                self.batteryWarnedFor20Percent = true
            }

            // Notify the observers of battery warning
            if warn {
                self.forEachObserver {
                    $0.idHandBatteryWarning(selectedIdHand, batteryPercentage: batteryLevel)
                }
            }
        })

    }


    /// Connects to all !D Hands in connected EAAccessory objects
    private func connectIdHands() {
        let idHandAccessories = connectedIdHandAccessories()
        for accessory in idHandAccessories {
            connect(accessory)
        }
    }


    /// Returns array of connected !D Hand EAAccessory objects
    private func connectedIdHandAccessories() -> [EAAccessory] {
        var supportedAccessories = [EAAccessory]()

        for accessory in EAAccessoryManager.sharedAccessoryManager().connectedAccessories {
            if isSupportedAccessory(accessory) {
                supportedAccessories.append(accessory)
            }
        }

        return supportedAccessories
    }


    /// Returns Bool if EAAccessory supports !D Hand protocol
    private func isSupportedAccessory(accessory: EAAccessory) -> Bool {
        return accessory.protocolStrings.contains(IdHandProtocol)
    }


    /// !D Hand from EAAccessory
    private func idHandForAccessory(accessory: EAAccessory) -> IdHand? {
        for idHand in connectedIdHands {
            if idHand.accessory == accessory {
                return idHand
            }
        }

        return nil
    }


    /// Connect to EAAccessory
    private func connect(accessory : EAAccessory) {
        if !isSupportedAccessory(accessory) {
            print("Connected accessory is not an !D Hand")
            return
        }

        // Check if this !D Hand is already connected
        if idHandForAccessory(accessory) != nil {
            print("Accessory already connected")
            return
        }

        // Create and connect an IdHand object
        let idHand = IdHand(accessory: accessory)
        idHand.initialize { () -> () in
            self.connectedIdHands.append(idHand)

            // If it's the only connected !D Hand, or the !D Hand that was selected but got disconnected, (re)select it
            if (idHand.supportsRegulation(self.idHandSettings.regulation) && self.selectedIdHand == nil && self.disconnectedLastSelectedIdHand == nil) || (self.selectedIdHand == nil && self.disconnectedLastSelectedIdHand != nil && self.disconnectedLastSelectedIdHand?.serial == idHand.serial) {
                self.selectedIdHand = idHand
            }

            // Notify the observers
            self.forEachObserver {
                $0.idHandDidConnect(idHand)
            }
        }
    }


    /// Disconnect EAAccessory
    private func disconnect(accessory : EAAccessory) {
        guard let idHand = idHandForAccessory(accessory), let index = connectedIdHands.indexOf(idHand) else {
            return
        }

        // Clear the removed !D Hand from the connected !D Hands array
        connectedIdHands.removeAtIndex(index)

        // Clear the variable that keeps track of the selected !D Hand if it's the one that disconnected.
        // Keep track of the last selected but disconnected !D Hand
        if selectedIdHand == idHand {
            disconnectedLastSelectedIdHand = selectedIdHand
            selectedIdHand = nil
        }

        // Tell the IdHand object to clean up
        idHand.disconnect()

        // Notify the observers
        self.forEachObserver {
            $0.idHandDidDisconnect(idHand)
        }
    }


    private func applySettingsToSelectedIdHand() {
        guard let selectedIdHand = selectedIdHand else {
            return
        }

        // Check if the settings can be applied (only if the regulation is supported)
        if selectedIdHand.supportsRegulation(idHandSettings.regulation!) {
            selectedIdHand.setRegulation(idHandSettings.regulation!) {
                // Make sure to get the correct power value from settings
                selectedIdHand.outputPower = self.idHandSettings.outputPower ?? self.idHandSettings.maximumOutputPower
                selectedIdHand.sessionType = self.idHandSettings.session
                selectedIdHand.target = self.idHandSettings.target
                selectedIdHand.select = self.idHandSettings.select
            }
        } else {
            // Regulation is not supported, reset it on the !D Hand
            self.selectedIdHand?.setRegulation(nil) {}

            // Deselect !D Hand
            print("Selected !D Hand is not compatible with this regulation, deselecting it")
            self.selectedIdHand = nil
        }
    }


    // MARK: -
    // MARK: IdHandSettingsDelegate

    func settingsDidUpdate() {
        applySettingsToSelectedIdHand()
    }
}
