//
//  Action.swift
//  IDHand2
//
//  Copyright © 2015 N.V. Nederlandsche Apparatenfabriek "NEDAP". All rights reserved.
//

import Foundation


// MARK: - 
// MARK: Action protocol

/// Action statuses with !D Hand
protocol Action: class {
    
    /// Prepares the action
    func prepare()
    
    /// Starts the action
    func start()
    
    /// Stops the action
    func stop()
    
    /// Clean-up of the action
    func cleanup()
}
