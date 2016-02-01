#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRReceivablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief The OutputPower packet contains the current configured RFID output power and the output power boundaries of the reader.
 */
@interface IDROutputPowerPacket : IDRReceivablePacket

/*! 
 * @brief Constructs an OutputPower packet from raw received data
 * @param data Byte array with data
 */
- (nonnull instancetype)initWithData:(nonnull NSData *)data;

/*! 
 * @brief Gets a string representation of this packet, suitable for logging purposes.
 * @return String representation of this packet.
 */
- (nonnull NSString *)toString;

/*! 
 * @brief Gets output power in tenths of dBm.
 * @return Output power in tenths of dBm (e.g. a value of 250 means 25.0 dBm)
 */
- (uint16_t)outputPower;

/*! 
 * @brief Gets the mimium output power in tenths of dBm.
 * @return Output power in tenths of dBm (e.g. a value of 140 means 14.0 dBm)
 */
- (uint16_t)minimumOutputPower;

/*! 
 * @brief Gets the maximum output power in tenths of dBm.
 * @return Output power in tenths of dBm (e.g. a value of 300 means 30.0 dBm)
 */
- (uint16_t)maximumOutputPower;

/*! 
 * @brief Gets output power in tenths of dBm.
 * @return Output power in tenths of dBm (e.g. a value of 250 means 25.0 dBm)
 */
@property(nonatomic, readonly, getter=outputPower) uint16_t outputPower;

/*! 
 * @brief Gets the mimium output power in tenths of dBm.
 * @return Output power in tenths of dBm (e.g. a value of 140 means 14.0 dBm)
 */
@property(nonatomic, readonly, getter=minimumOutputPower) uint16_t minimumOutputPower;

/*! 
 * @brief Gets the maximum output power in tenths of dBm.
 * @return Output power in tenths of dBm (e.g. a value of 300 means 30.0 dBm)
 */
@property(nonatomic, readonly, getter=maximumOutputPower) uint16_t maximumOutputPower;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs an OutputPower packet from raw received data
 * @param data Byte array with data
 */
+ (nonnull instancetype)packetWithData:(nonnull NSData *)data;


@end
