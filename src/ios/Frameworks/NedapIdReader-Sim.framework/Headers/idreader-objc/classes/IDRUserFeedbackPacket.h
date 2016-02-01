#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRSendablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief Command to perform user feedback (sound and vibration)
 * 
 * @note If a UserFeedback packet is sent while the reader is still busy with another user feedback, the packet is ignored.
 * @note Be careful not to send many packets in a short time frame. It is recommended to limit to a maximum of 1 feedback packet per 100ms.
 */
@interface IDRUserFeedbackPacket : IDRSendablePacket

/*! 
 * @brief Constructs a UserFeedback packet.
 * @param vibration The vibration pattern
 * @param speaker The sound type
 */
- (nonnull instancetype)initWithVibration:(IDRVibrationPattern)vibration speaker:(IDRSpeakerSound)speaker;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a UserFeedback packet.
 * @param vibration The vibration pattern
 * @param speaker The sound type
 */
+ (nonnull instancetype)packetWithVibration:(IDRVibrationPattern)vibration speaker:(IDRSpeakerSound)speaker;


@end
