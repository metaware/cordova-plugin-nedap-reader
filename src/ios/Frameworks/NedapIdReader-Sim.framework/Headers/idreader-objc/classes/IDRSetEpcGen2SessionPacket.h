#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRSendablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief Command to configure the EPC Gen2 session parameters. The reader will respond with a EpcGen2Session response.
 */
@interface IDRSetEpcGen2SessionPacket : IDRSendablePacket

/*! 
 * @brief Construct a SetEpcGen2Session command.
 * @param session EPC Gen2 session
 * @param target EPC Gen2 target
 * @param select EPC Gen2 select state
 * @param autoFlip Configures after how many query rounds the reader should switch to the other target. Set to 0 for no target flipping.
 */
- (nonnull instancetype)initWithSession:(IDRSession)session target:(IDRTarget)target select:(IDRSelect)select autoFlip:(uint8_t)autoFlip;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Construct a SetEpcGen2Session command.
 * @param session EPC Gen2 session
 * @param target EPC Gen2 target
 * @param select EPC Gen2 select state
 * @param autoFlip Configures after how many query rounds the reader should switch to the other target. Set to 0 for no target flipping.
 */
+ (nonnull instancetype)packetWithSession:(IDRSession)session target:(IDRTarget)target select:(IDRSelect)select autoFlip:(uint8_t)autoFlip;


@end
