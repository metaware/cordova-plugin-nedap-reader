#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief Speaker sound enumeration
 */
typedef NS_ENUM(uint8_t, IDRSpeakerSound) {
    IDRSpeakerSoundNone = 0, ///< No sound
    IDRSpeakerSoundNotify = 1, ///< Notify sound
    IDRSpeakerSoundNotifySubtle = 2, ///< Subtle notify sound (e.g. observing new EPCs)
    IDRSpeakerSoundSuccess = 3, ///< Success sound
    IDRSpeakerSoundFailure = 4, ///< Failure sound
    IDRSpeakerSoundAlert = 5, ///< Alert sound
    IDRSpeakerSoundConnect = 6, ///< Connect sound
    IDRSpeakerSoundDisconnect = 7, ///< Disconnect sound
    IDRSpeakerSoundBatteryLow = 8, ///< Battery low sound
};

/*! 
 * @brief Speaker sound enumeration
 */
@interface IDRSpeakerSoundWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRSpeakerSound enumeration value.
 * @param enumValue The IDRSpeakerSound value.
 * @return IDRSpeakerSound instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRSpeakerSound)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRSpeakerSound value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRSpeakerSound value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRSpeakerSound value;

/*!
 * @brief Creates a wrapped object with a IDRSpeakerSound enumeration value.
 * @param value The IDRSpeakerSound value.
 * @return IDRSpeakerSound instance representing the enum value.
 */
+(nonnull instancetype) speakerSoundWrapperWithValue:(IDRSpeakerSound)value;

/*!
 * @brief Retrieves an array with all SpeakerSounds wrapped in IDRSpeakerSoundWrapper objects
 * @return NSArray with all SpeakerSounds wrapped in IDRSpeakerSoundWrapper objects
 */
+(nonnull NSArray<IDRSpeakerSoundWrapper *> *) allSpeakerSounds;

@end
