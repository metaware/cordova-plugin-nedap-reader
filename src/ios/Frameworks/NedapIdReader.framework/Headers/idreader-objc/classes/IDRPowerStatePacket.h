#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRReceivablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief The PowerState packet is received as a response to the GetPowerState command and contains the current battery level, battery health and power source.
 */
@interface IDRPowerStatePacket : IDRReceivablePacket

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
 * @brief Gets the current power source
 * @return The current power source
 */
- (IDRPowerSource)powerSource;

/*! 
 * @brief Gets the current battery level
 * @return The current battery level between 0 and 100%
 */
- (uint8_t)batteryLevel;

/*! 
 * @brief Gets the current battery health
 * @return The current battery health between 0 and 100%
 */
- (uint8_t)batteryHealth;

/*! 
 * @brief Gets the current power source
 * @return The current power source
 */
@property(nonatomic, readonly, getter=powerSource) IDRPowerSource powerSource;

/*! 
 * @brief Gets the current battery level
 * @return The current battery level between 0 and 100%
 */
@property(nonatomic, readonly, getter=batteryLevel) uint8_t batteryLevel;

/*! 
 * @brief Gets the current battery health
 * @return The current battery health between 0 and 100%
 */
@property(nonatomic, readonly, getter=batteryHealth) uint8_t batteryHealth;

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
