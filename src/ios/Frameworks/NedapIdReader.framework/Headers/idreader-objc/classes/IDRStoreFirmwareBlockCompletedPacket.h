#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRReceivablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief The StoreFirmwareBlockCompleted packet is received as a response to the StoreFirmwareBlock command.
 *
 * It acknowledges that the firmware data block is received correctly and stored into flash.
 */
@interface IDRStoreFirmwareBlockCompletedPacket : IDRReceivablePacket

/*! 
 * @brief Constructs a StoreFirmwareBlockCompleted packet from raw received data
 * @param data Byte array with data
 */
- (nonnull instancetype)initWithData:(nonnull NSData *)data;

/*! 
 * @brief Gets a string representation of this packet, suitable for logging purposes.
 * @return String representation of this packet
 */
- (nonnull NSString *)toString;

/*! 
 * @brief Gets the packet number which is received by the reader
 * @return The packet number
 */
- (uint16_t)packetNumber;

/*! 
 * @brief Gets the packet number which is received by the reader
 * @return The packet number
 */
@property(nonatomic, readonly, getter=packetNumber) uint16_t packetNumber;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a StoreFirmwareBlockCompleted packet from raw received data
 * @param data Byte array with data
 */
+ (nonnull instancetype)packetWithData:(nonnull NSData *)data;


@end
