#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRReceivablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief A ButtonEvent is received when the user presses or releases the button.
 */
@interface IDRButtonEventPacket : IDRReceivablePacket

/*! 
 * @brief Constructs a ButtonEvent packet from raw received data
 * @param data Byte array with data
 */
- (nonnull instancetype)initWithData:(nonnull NSData *)data;

/*! 
 * @brief Gets a string representation of this packet, suitable for logging purposes.
 * @return String representation of this packet.
 */
- (nonnull NSString *)toString;

/*! 
 * @brief Gets the button ID (currently always 0x00)
 * @return The button ID
 */
- (uint8_t)buttonId;

/*! 
 * @brief Gets the ButtonEventType (e.g. down press or release)
 * @return Down when button is pressed, up when button is released.
 */
- (IDRButtonEventType)eventType;

/*! 
 * @brief Gets the button ID (currently always 0x00)
 * @return The button ID
 */
@property(nonatomic, readonly, getter=buttonId) uint8_t buttonId;

/*! 
 * @brief Gets the ButtonEventType (e.g. down press or release)
 * @return Down when button is pressed, up when button is released.
 */
@property(nonatomic, readonly, getter=eventType) IDRButtonEventType eventType;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a ButtonEvent packet from raw received data
 * @param data Byte array with data
 */
+ (nonnull instancetype)packetWithData:(nonnull NSData *)data;


@end
