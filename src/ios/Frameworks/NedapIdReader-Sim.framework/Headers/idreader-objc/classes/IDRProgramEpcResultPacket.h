#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRReceivablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief The ProgramEpcResult packet is received when the ProgramEpc command is finished.
 */
@interface IDRProgramEpcResultPacket : IDRReceivablePacket

/*! 
 * @brief Constructs a PowerState packet from raw received data
 * @param data Byte array with data
 */
- (nonnull instancetype)initWithData:(nonnull NSData *)data;

/*! 
 * @brief Gets a string representation of this packet, suitable for logging purposes.
 * @return String representation of this packet.
 */
- (nonnull NSString *)toString;

/*! 
 * @brief Gets the result code of the ProgramEpc command.
 * @return The program EPC result code
 */
- (IDRProgramEpcResultCode)resultCode;

/*! 
 * @brief Gets the binary TID of the tag
 * @return Byte array with the TID
 */
- (nonnull NSData *)tid;

/*! 
 * @brief Gets the EPC encoding type used
 * @return The EPC encoding type
 */
- (IDREpcEncoding)encoding;

/*! 
 * @brief Gets the source used for serialization (conversion from GTIN to SGTIN)
 * @return The serialization source
 */
- (IDRSerializationSource)serializationSource;

/*! 
 * @brief Gets the binary EPC of the tag
 * @return Byte array with the EPC
 */
- (nonnull NSData *)epc;

/*! 
 * @brief Gets the EPC of the tag represented as hexadecimal string
 * @return Hexadecimal string with the EPC
 */
- (nonnull NSString *)epcAsHexString;

/*! 
 * @brief Gets the TID of the tag represented as hexadecimal string
 * @return Hexadecimal string with the TID
 */
- (nonnull NSString *)tidAsHexString;

/*! 
 * @brief Gets the result code of the ProgramEpc command.
 * @return The program EPC result code
 */
@property(nonatomic, readonly, getter=resultCode) IDRProgramEpcResultCode resultCode;

/*! 
 * @brief Gets the binary TID of the tag
 * @return Byte array with the TID
 */
@property(nonatomic, nonnull, readonly, getter=tid) NSData * tid;

/*! 
 * @brief Gets the EPC encoding type used
 * @return The EPC encoding type
 */
@property(nonatomic, readonly, getter=encoding) IDREpcEncoding encoding;

/*! 
 * @brief Gets the source used for serialization (conversion from GTIN to SGTIN)
 * @return The serialization source
 */
@property(nonatomic, readonly, getter=serializationSource) IDRSerializationSource serializationSource;

/*! 
 * @brief Gets the binary EPC of the tag
 * @return Byte array with the EPC
 */
@property(nonatomic, nonnull, readonly, getter=epc) NSData * epc;

/*! 
 * @brief Gets the EPC of the tag represented as hexadecimal string
 * @return Hexadecimal string with the EPC
 */
@property(nonatomic, nonnull, readonly, getter=epcAsHexString) NSString * epcAsHexString;

/*! 
 * @brief Gets the TID of the tag represented as hexadecimal string
 * @return Hexadecimal string with the TID
 */
@property(nonatomic, nonnull, readonly, getter=tidAsHexString) NSString * tidAsHexString;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a PowerState packet from raw received data
 * @param data Byte array with data
 */
+ (nonnull instancetype)packetWithData:(nonnull NSData *)data;


@end
