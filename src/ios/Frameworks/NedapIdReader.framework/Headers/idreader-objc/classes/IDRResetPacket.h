#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRSendablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief Command to reset the reader. This will eventually stop reading and reset all the non-persistent settings to their startup defaults. The reader will respond with a ResetCompleted response.
 */
@interface IDRResetPacket : IDRSendablePacket

/*! 
 * @brief Constructs a Reset packet.
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
 * @brief Constructs a Reset packet.
 */
+ (nonnull instancetype)packet;


@end
