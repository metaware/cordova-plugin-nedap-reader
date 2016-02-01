#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRSendablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief Command to set the user LED mode. The reader will respond with a UserLedMode response.
 *
 * This command can configure the white LED around the !D Hand button.
 * When de device is turned on (without an active connection), the user LED will be in the 'On' mode.
 */
@interface IDRSetUserLedModePacket : IDRSendablePacket

/*! 
 * @brief Constructs a SetUserLedMode command.
 * @param mode The mode to use (e.g. on, off or blinking)
 */
- (nonnull instancetype)initWithMode:(IDRLedMode)mode;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a SetUserLedMode command.
 * @param mode The mode to use (e.g. on, off or blinking)
 */
+ (nonnull instancetype)packetWithMode:(IDRLedMode)mode;


@end
