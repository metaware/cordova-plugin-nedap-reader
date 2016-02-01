#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRSendablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief Command to start a smart inventory.
 *
 * This will start a continuous RFID inventory which is optimized for stock taking.
 * E.g. when the antenna moves near metal objects, any antenna mismatch error is caught and stock taking is continued after a small pause.
 * Also the reader can make decisions to optimize the battery life of the reader.
 */
@interface IDRStartInventorySmartPacket : IDRSendablePacket

/*! 
 * @brief Constructs a StartSmartInventory command.
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
 * @brief Constructs a StartSmartInventory command.
 */
+ (nonnull instancetype)packet;


@end
