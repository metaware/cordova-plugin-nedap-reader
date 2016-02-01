#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRReceivablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief An Error packet is received when something has gone wrong in the reader.
 *
 * An error contains a category and a code within the category. Use isProtocolError, isStateError, etc to check for the error type.
 */
@interface IDRErrorPacket : IDRReceivablePacket

/*! 
 * @brief Constructs a Error packet from raw received data
 * @param data Byte array with data
 */
- (nonnull instancetype)initWithData:(nonnull NSData *)data;

/*! 
 * @brief Gets a string representation of this packet, suitable for logging purposes.
 * @return String representation of this packet.
 */
- (nonnull NSString *)toString;

/*! 
 * @brief Gets the error category of this error.
 * @return The error category
 */
- (IDRErrorCategory)category;

/*! 
 * @brief Gets the raw error code within the category.
 * @return The error code
 */
- (uint8_t)code;

/*! 
 * @brief Check whether this error is of a given ProtocolError type.
 * @param error The ProtocolError type to check for
 * @return true if this error is of the given type, false if not.
 */
- (BOOL)isProtocolError:(IDRProtocolError) error;

/*! 
 * @brief Check whether this error is of a given StateError type.
 * @param error The StateError type to check for
 * @return true if this error is of the given type, false if not.
 */
- (BOOL)isStateError:(IDRStateError) error;

/*! 
 * @brief Check whether this error is of a given ConfigurationError type.
 * @param error The ConfigurationError type to check for
 * @return true if this error is of the given type, false if not.
 */
- (BOOL)isConfigurationError:(IDRConfigurationError) error;

/*! 
 * @brief Check whether this error is of a given HardwareError type.
 * @param error The HardwareError type to check for
 * @return true if this error is of the given type, false if not.
 */
- (BOOL)isHardwareError:(IDRHardwareError) error;

/*! 
 * @brief Check whether this error is of a given RfidError type.
 * @param error The RfidError type to check for
 * @return true if this error is of the given type, false if not.
 */
- (BOOL)isRfidError:(IDRRfidError) error;

/*! 
 * @brief Check whether this error is of a given OtherError type.
 * @param error The OtherError type to check for
 * @return true if this error is of the given type, false if not.
 */
- (BOOL)isOtherError:(IDROtherError) error;

/*! 
 * @brief Gets the error category of this error.
 * @return The error category
 */
@property(nonatomic, readonly, getter=category) IDRErrorCategory category;

/*! 
 * @brief Gets the raw error code within the category.
 * @return The error code
 */
@property(nonatomic, readonly, getter=code) uint8_t code;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a Error packet from raw received data
 * @param data Byte array with data
 */
+ (nonnull instancetype)packetWithData:(nonnull NSData *)data;


@end
