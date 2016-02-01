#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRSendablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief Represents a packet that can be sent to the reader.
 */
@interface IDRProgramEpcPacket : IDRSendablePacket

/*! 
 * @brief Programs the EPC bank with the supplied data. The reader will respond with a ProgramEpcResult response.
 * 
 * @see programRaw
 * @see programSgtin96UsingSuppliedSerial
 * 
 * @param encoding The encoding method to use.
 * @param password The access password for if the tag's EPC bank is locked, or 0 otherwise.
 * @param epcOrGtin Binary EPC data (in case of raw EPC encoding) or ASCII-encoded 14-character GTIN string.
 * @param serializationSource The serialization source to use (ignored when encoding is raw EPC).
 * @param companyPrefixLength Length (in digits) of company prefix in supplied GTIN. Must be between 6 and 12 (inclusive).
 * @param filterValue SGTIN EPC filter value as defined in GS1 standard.
 * @param serial The serial number for when serialization source is Supplied.
 */
- (nonnull instancetype)initWithEncoding:(IDREpcEncoding)encoding password:(uint32_t)password epcOrGtin:(nonnull NSData *)epcOrGtin serializationSource:(IDRSerializationSource)serializationSource companyPrefixLength:(uint8_t)companyPrefixLength filterValue:(IDRSgtinEpcFilterValue)filterValue serial:(nonnull NSData *)serial;

/*! 
 * @brief Programs the EPC bank of a tag with the supplied data.
 * 
 * @param epc The binary EPC to program.
 * @param password The access password for if the tag's EPC bank is locked, or 0 otherwise.
 */
+ (nonnull IDRProgramEpcPacket *)programRawWithEpc:(nonnull NSData *) epc password:(uint32_t) password;

/*! 
 * @brief Programs the EPC bank of a tag with an SGTIN-96 and supplied serial
 * 
 * @param gtin String containing the GTIN.
 * @param companyPrefixLength Length (in digits) of company prefix in supplied GTIN. Must be between 6 and 12 (inclusive).
 * @param filterValue SGTIN EPC filter value as defined in GS1 standard.
 * @param serial Serial as ASCII-encoded string to use to produce SGTIN from GTIN. Should be a decimal string without any leading zeros, representing a value between 0 and 274877906943 (inclusive).
 * @param password The access password for if the tag's EPC bank is locked, or 0 otherwise.
 */
+ (nonnull IDRProgramEpcPacket *)programSgtin96UsingSuppliedSerialWithGtin:(nonnull NSString *) gtin companyPrefixLength:(uint8_t) companyPrefixLength filterValue:(IDRSgtinEpcFilterValue) filterValue serial:(nonnull NSString *) serial password:(uint32_t) password;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Programs the EPC bank with the supplied data. The reader will respond with a ProgramEpcResult response.
 * 
 * @see programRaw
 * @see programSgtin96UsingSuppliedSerial
 * 
 * @param encoding The encoding method to use.
 * @param password The access password for if the tag's EPC bank is locked, or 0 otherwise.
 * @param epcOrGtin Binary EPC data (in case of raw EPC encoding) or ASCII-encoded 14-character GTIN string.
 * @param serializationSource The serialization source to use (ignored when encoding is raw EPC).
 * @param companyPrefixLength Length (in digits) of company prefix in supplied GTIN. Must be between 6 and 12 (inclusive).
 * @param filterValue SGTIN EPC filter value as defined in GS1 standard.
 * @param serial The serial number for when serialization source is Supplied.
 */
+ (nonnull instancetype)packetWithEncoding:(IDREpcEncoding)encoding password:(uint32_t)password epcOrGtin:(nonnull NSData *)epcOrGtin serializationSource:(IDRSerializationSource)serializationSource companyPrefixLength:(uint8_t)companyPrefixLength filterValue:(IDRSgtinEpcFilterValue)filterValue serial:(nonnull NSData *)serial;


@end
