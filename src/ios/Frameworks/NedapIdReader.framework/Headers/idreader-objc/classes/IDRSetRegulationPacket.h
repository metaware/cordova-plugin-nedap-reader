#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRSendablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief Command to configure the RFID regulation. The reader will respond with a RegulationPacket response.
 */
@interface IDRSetRegulationPacket : IDRSendablePacket

/*! 
 * @brief Constructs a SetRegulation packet
 * @param regulation The RFID regulation to use
 */
- (nonnull instancetype)initWithRegulation:(IDRRegulation)regulation;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a SetRegulation packet
 * @param regulation The RFID regulation to use
 */
+ (nonnull instancetype)packetWithRegulation:(IDRRegulation)regulation;


@end
