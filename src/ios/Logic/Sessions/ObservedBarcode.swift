//
//  ObservedBarcode.swift
//  IDHand2
//
//  Copyright © 2015 N.V. Nederlandsche Apparatenfabriek "NEDAP". All rights reserved.
//

import Foundation


/// Observed barcode object keeps track of the code & type
class ObservedBarcode {

    /// Barcode value, e.g. 0123456789
    var barcodeValue : String
    
    /// Barcode type, e.g. EAN13, Code39, ..
    var barcodeType : String


    init(value: String, type: String) {
        barcodeValue = value
        barcodeType = type
    }
}
