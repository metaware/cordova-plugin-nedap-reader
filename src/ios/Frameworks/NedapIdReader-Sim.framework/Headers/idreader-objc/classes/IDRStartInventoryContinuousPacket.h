#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRSendablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief Command to start low-level continuous EPC Gen2 RFID inventory
 */
@interface IDRStartInventoryContinuousPacket : IDRSendablePacket

/*! 
 * @brief Constructs an StartInventoryContinuous command.
 */
- (nonnull instancetype)init;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs an StartInventoryContinuous command.
 */
+ (nonnull instancetype)packet;


@end
