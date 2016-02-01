#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRReceivablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief The Bye packet is received as a response to the Hello command.
 */
@interface IDRByePacket : IDRReceivablePacket

/*! 
 * @brief Gets a string representation of this packet, suitable for logging purposes.
 * @return String representation of this packet
 */
- (nonnull NSString *)toString;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;


@end
