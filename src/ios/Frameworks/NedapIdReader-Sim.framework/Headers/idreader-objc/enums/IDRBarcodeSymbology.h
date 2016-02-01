#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief Barcode symbology, representing a barcode type
 */
typedef NS_ENUM(uint8_t, IDRBarcodeSymbology) {
    IDRBarcodeSymbologyEan8 = 0, ///< EAN 8
    IDRBarcodeSymbologyEan13 = 1, ///< EAN 13
    IDRBarcodeSymbologyUpcA = 2, ///< UPC A
    IDRBarcodeSymbologyUpcE = 3, ///< UPC E
    IDRBarcodeSymbologyEan128 = 4, ///< GS1-128
    IDRBarcodeSymbologyCodabar = 5, ///< Codabar
    IDRBarcodeSymbologyCode11 = 6, ///< Code 11
    IDRBarcodeSymbologyCode39 = 7, ///< Code 39
    IDRBarcodeSymbologyCode93 = 8, ///< Code 93
    IDRBarcodeSymbologyInterleaved2of5 = 9, ///< Interleaved 2 of 5
    IDRBarcodeSymbologyCode128 = 10, ///< Code 128
    IDRBarcodeSymbologyMsi = 11, ///< MSI
    IDRBarcodeSymbologyQrCode = 12, ///< QR Code
    IDRBarcodeSymbologyDataMatrix = 13, ///< Data matrix
    IDRBarcodeSymbologyPdf417 = 14, ///< PDF 417
    IDRBarcodeSymbologyGs1Databar = 15, ///< GS1 Databar
    IDRBarcodeSymbologyGs1DatabarLimited = 16, ///< GS1 Databar limited
    IDRBarcodeSymbologyGs1DatabarExpanded = 17, ///< GS1 Databar expanded
    IDRBarcodeSymbologyStandard2Of5 = 18, ///< Standard 2 of 5
    IDRBarcodeSymbologyIndustrial2Of5 = 19, ///< Industrial 2 of 5
    IDRBarcodeSymbologyMatrix2Of5 = 20, ///< Matrix 2 of 5
    IDRBarcodeSymbologyItf14 = 21, ///< ITF 14
    IDRBarcodeSymbologyItf6 = 22, ///< ITF 6
    IDRBarcodeSymbologyAim128 = 23, ///< AIM 128
    IDRBarcodeSymbologyCode128Fnc3 = 24, ///< Code 128 FNC3
    IDRBarcodeSymbologyOther = 255, ///< Other (unknown) barcode symbology
};

/*! 
 * @brief Barcode symbology, representing a barcode type
 */
@interface IDRBarcodeSymbologyWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRBarcodeSymbology enumeration value.
 * @param enumValue The IDRBarcodeSymbology value.
 * @return IDRBarcodeSymbology instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRBarcodeSymbology)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRBarcodeSymbology value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRBarcodeSymbology value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRBarcodeSymbology value;

/*!
 * @brief Creates a wrapped object with a IDRBarcodeSymbology enumeration value.
 * @param value The IDRBarcodeSymbology value.
 * @return IDRBarcodeSymbology instance representing the enum value.
 */
+(nonnull instancetype) barcodeSymbologyWrapperWithValue:(IDRBarcodeSymbology)value;

/*!
 * @brief Retrieves an array with all BarcodeSymbologys wrapped in IDRBarcodeSymbologyWrapper objects
 * @return NSArray with all BarcodeSymbologys wrapped in IDRBarcodeSymbologyWrapper objects
 */
+(nonnull NSArray<IDRBarcodeSymbologyWrapper *> *) allBarcodeSymbologys;

@end
