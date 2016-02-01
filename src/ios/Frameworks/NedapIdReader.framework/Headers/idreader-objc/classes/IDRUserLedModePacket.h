#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRReceivablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief The UserLedMode packet contains the current state of the user LED.
 */
@interface IDRUserLedModePacket : IDRReceivablePacket

/*! 
 * @brief Constructs a UserLedMode packet from raw received data
 * @param data Byte array with data
 */
- (nonnull instancetype)initWithData:(nonnull NSData *)data;

/*! 
 * @brief Gets the LED ID (currently always 0x00)
 * @return LED ID
 */
- (uint8_t)ledId;

/*! 
 * @brief Gets the current mode
 * @return LedMode (e.g. on, off or blinking)
 */
- (IDRLedMode)mode;

/*! 
 * @brief Gets a string representation of this packet, suitable for logging purposes.
 * @return String representation of this packet.
 */
- (nonnull NSString *)toString;

/*! 
 * @brief Gets the LED ID (currently always 0x00)
 * @return LED ID
 */
@property(nonatomic, readonly, getter=ledId) uint8_t ledId;

/*! 
 * @brief Gets the current mode
 * @return LedMode (e.g. on, off or blinking)
 */
@property(nonatomic, readonly, getter=mode) IDRLedMode mode;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a UserLedMode packet from raw received data
 * @param data Byte array with data
 */
+ (nonnull instancetype)packetWithData:(nonnull NSData *)data;


@end
