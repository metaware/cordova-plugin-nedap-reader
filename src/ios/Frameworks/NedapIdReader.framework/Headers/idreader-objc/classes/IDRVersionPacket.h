#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRReceivablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief The Version packet is received as a response to the GetVersion command.
 */
@interface IDRVersionPacket : IDRReceivablePacket

/*! 
 * @brief Constructs a Version packet from raw received data
 * @param data Byte array with data
 */
- (nonnull instancetype)initWithData:(nonnull NSData *)data;

/*! 
 * @brief Gets a string representation of this packet, suitable for logging purposes.
 * @return String representation of this packet
 */
- (nonnull NSString *)toString;

/*! 
 * @brief Retrieves the hardware version as reported by the reader.
 * @return Hardware version
 */
- (uint8_t)hardwareVersion;

/*! 
 * @brief Retrieves the firmware version as reported by the reader.
 * @return Firmware version
 */
- (uint16_t)softwareVersion;

/*! 
 * @brief Retrieves the hardware version as reported by the reader.
 * @return Hardware version
 */
@property(nonatomic, readonly, getter=hardwareVersion) uint8_t hardwareVersion;

/*! 
 * @brief Retrieves the firmware version as reported by the reader.
 * @return Firmware version
 */
@property(nonatomic, readonly, getter=softwareVersion) uint16_t softwareVersion;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a Version packet from raw received data
 * @param data Byte array with data
 */
+ (nonnull instancetype)packetWithData:(nonnull NSData *)data;


@end
