#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRReceivablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief The BarcodeReaderData packet contains the barcode symbology and barcode data for a successful barcode read.
 */
@interface IDRBarcodeReaderDataPacket : IDRReceivablePacket

/*! 
 * @brief Constructs a BarcodeReaderData packet.
 * @param data Raw byte array with packet data.
 */
- (nonnull instancetype)initWithData:(nonnull NSData *)data;

/*! 
 * @brief Gets a string representation of this packet, suitable for logging purposes.
 * @return String representation of this packet.
 */
- (nonnull NSString *)toString;

/*! 
 * @brief Gets the AIM Symbology ID
 * 
 * @return String containing the AIM Symbology ID (3 characters) e.g. "]E0"
 */
- (nonnull NSString *)aimId;

/*! 
 * @brief Gets the barcode symbology
 * 
 * @return the barcode symbology
 */
- (IDRBarcodeSymbology)symbology;

/*! 
 * @brief Gets the barcode symbology name as a string.
 * This is a convenience function that calls the toString for the symbology
 * 
 * @return Barcode symbology name as a string, e.g. "EAN 13".
 */
- (nonnull NSString *)symbologyName;

/*! 
 * @brief Gets the raw barcode data. The encoding of the barcode data depends on the barcode symbology.
 * 
 * @return Byte array with barcode data.
 */
- (nonnull NSData *)barcodeData;

/*! 
 * @brief Gets the AIM Symbology ID
 * 
 * @return String containing the AIM Symbology ID (3 characters) e.g. "]E0"
 */
@property(nonatomic, nonnull, readonly, getter=aimId) NSString * aimId;

/*! 
 * @brief Gets the barcode symbology
 * 
 * @return the barcode symbology
 */
@property(nonatomic, readonly, getter=symbology) IDRBarcodeSymbology symbology;

/*! 
 * @brief Gets the barcode symbology name as a string.
 * This is a convenience function that calls the toString for the symbology
 * 
 * @return Barcode symbology name as a string, e.g. "EAN 13".
 */
@property(nonatomic, nonnull, readonly, getter=symbologyName) NSString * symbologyName;

/*! 
 * @brief Gets the raw barcode data. The encoding of the barcode data depends on the barcode symbology.
 * 
 * @return Byte array with barcode data.
 */
@property(nonatomic, nonnull, readonly, getter=barcodeData) NSData * barcodeData;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a BarcodeReaderData packet.
 * @param data Raw byte array with packet data.
 */
+ (nonnull instancetype)packetWithData:(nonnull NSData *)data;


@end
