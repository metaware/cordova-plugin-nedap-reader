//
//  ObservationCounter.swift
//  IDHand2
//
//  Copyright © 2015 N.V. Nederlandsche Apparatenfabriek "NEDAP". All rights reserved.
//

import Foundation


/// Responsible for counting observations (only in memory)
class ObservationCounter {

    /// Unique observations set (ordered)
    private var uniqueObservations : NSMutableOrderedSet

    /// Total number of observations (including duplicates)
    private var observationCount : Int


    init() {
        uniqueObservations = NSMutableOrderedSet()
        observationCount = 0
    }


    /// Return an array with all observations
    func epcObservations() -> [EpcObservation] {
        let returnArray = uniqueObservations.array as! [EpcObservation]
        return returnArray
    }


    /// Return the number of unique observations
    func uniqueCount() -> Int {
        return uniqueObservations.count
    }


    /// Return the number of total (not unique) observations
    func totalCount() -> Int {
        return observationCount
    }


    /// Processes incoming EPC observations.
    func addEpcObservations(observations : [EpcObservation]) -> Int {
        // Increase count of total observations
        self.observationCount += observations.count

        // Add new observations, update existing
        var newObservationCount : Int  = 0
        for observation in observations {
            let index = uniqueObservations.indexOfObject(observation)

            if (index != Foundation.NSNotFound) {
                let existingObservation = uniqueObservations.objectAtIndex(index) as! EpcObservation
                existingObservation.count++
            } else {
                uniqueObservations.addObject(observation)
                newObservationCount++
            }
        }

        return newObservationCount
    }


    /// Reset the observation counter
    func reset() {
        self.uniqueObservations.removeAllObjects()
        self.observationCount = 0
    }
}
