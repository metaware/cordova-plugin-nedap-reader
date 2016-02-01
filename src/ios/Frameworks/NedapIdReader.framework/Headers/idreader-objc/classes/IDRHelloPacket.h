#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRSendablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief The Hello command can be used to verify the communication with the reader. The reader will response with the Bye response.
 */
@interface IDRHelloPacket : IDRSendablePacket

/*! 
 * @brief Constructs a Hello packet.
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
 * @brief Constructs a Hello packet.
 */
+ (nonnull instancetype)packet;


@end
