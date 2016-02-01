#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRReceivablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief The SerialNumber packet is received as a response to the GetSerialNumber command.
 */
@interface IDRSerialNumberPacket : IDRReceivablePacket

/*! 
 * @brief Constructs a SerialNumber packet from raw received data
 * @param data Byte array with data
 */
- (nonnull instancetype)initWithData:(nonnull NSData *)data;

/*! 
 * @brief Gets a string representation of this packet, suitable for logging purposes.
 * @return String representation of this packet
 */
- (nonnull NSString *)toString;

/*! 
 * @brief Gets the serial number as reported by the reader.
 * @return String with the serial number.
 */
- (nonnull NSString *)serialNumber;

/*! 
 * @brief Gets the serial number as reported by the reader.
 * @return String with the serial number.
 */
@property(nonatomic, nonnull, readonly, getter=serialNumber) NSString * serialNumber;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a SerialNumber packet from raw received data
 * @param data Byte array with data
 */
+ (nonnull instancetype)packetWithData:(nonnull NSData *)data;


@end
