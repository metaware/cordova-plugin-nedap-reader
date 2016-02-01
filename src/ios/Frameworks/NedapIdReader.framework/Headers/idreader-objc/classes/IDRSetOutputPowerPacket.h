#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRSendablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief Command to configure the RF output power.
 *
 * If the output power is too high or too low, the reader will configure itself to its maximum or minimum output power respectively.
 */
@interface IDRSetOutputPowerPacket : IDRSendablePacket

/*! 
 * @brief Constructs a SetOutputPower command.
 * @param powerInTenthsOfDBm Power in tenths of dBm. For e.g. 25.0 dBm, this value should be 250.
 */
- (nonnull instancetype)initWithPowerInTenthsOfDBm:(uint16_t)powerInTenthsOfDBm;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a SetOutputPower command.
 * @param powerInTenthsOfDBm Power in tenths of dBm. For e.g. 25.0 dBm, this value should be 250.
 */
+ (nonnull instancetype)packetWithPowerInTenthsOfDBm:(uint16_t)powerInTenthsOfDBm;


@end
