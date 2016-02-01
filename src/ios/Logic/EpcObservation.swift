//
//  EpcObservation.swift
//  IDHand2
//
//  Copyright © 2015 N.V. Nederlandsche Apparatenfabriek "NEDAP". All rights reserved.
//

import Foundation


/// Contains one EPC observation; hexadecimal value, timestamp, rssi and count
class EpcObservation: NSObject {
    
    /// Hexadecimal value of the EPC observation
    var hex : String = ""
    
    /// Timestamp of when the EPC was observed
    var timestamp : NSDate = NSDate()
    
    /// RSSI value of EPC observation
    var rssi : Int16 = 0
    
    /// Number of times this EPC has been observed
    var count : Int = 0 {
        didSet {
            self.timestamp = NSDate()
        }
    }


    /// Initializes an EPC observation
    init(hex : String, rssi : Int16, count : Int) {
        self.hex = hex
        self.rssi = rssi
        self.count = count
    }
    
    
    /// Override for ObjC compatible equality
    override var hash: Int {
        return hex.hashValue
    }


    /// Override for ObjC compatible equality
    override func isEqual(object: AnyObject?) -> Bool {
        if let object = object as? EpcObservation {
            return hex == object.hex
        } else {
            return false
        }
    }


    /// Override for ObjC compatible description
    override var description : String {
        return "EpcObservation(\(self.hex), \(self.timestamp), \(self.rssi), \(self.count)"
    }
}


/// Compares EpcObservation based on hex value
func ==(lhs: EpcObservation, rhs: EpcObservation) -> Bool {
    return lhs.hex == rhs.hex
}
