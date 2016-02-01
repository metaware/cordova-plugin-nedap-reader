#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief Vibration pattern enum
 */
typedef NS_ENUM(uint8_t, IDRVibrationPattern) {
    IDRVibrationPatternNone = 0, ///< No vibration
    IDRVibrationPatternWeakSingle = 1, ///< 1 weak vibration
    IDRVibrationPatternWeakDouble = 2, ///< 2 weak vibrations
    IDRVibrationPatternWeakTriple = 3, ///< 3 weak vibrations
    IDRVibrationPatternWeakQuadruple = 7, ///< 4 weak vibrations
    IDRVibrationPatternStrongSingle = 4, ///< 1 strong vibration
    IDRVibrationPatternStrongDouble = 5, ///< 2 strong vibrations
    IDRVibrationPatternStrongTriple = 6, ///< 3 strong vibrations
};

/*! 
 * @brief Vibration pattern enum
 */
@interface IDRVibrationPatternWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRVibrationPattern enumeration value.
 * @param enumValue The IDRVibrationPattern value.
 * @return IDRVibrationPattern instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRVibrationPattern)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRVibrationPattern value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRVibrationPattern value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRVibrationPattern value;

/*!
 * @brief Creates a wrapped object with a IDRVibrationPattern enumeration value.
 * @param value The IDRVibrationPattern value.
 * @return IDRVibrationPattern instance representing the enum value.
 */
+(nonnull instancetype) vibrationPatternWrapperWithValue:(IDRVibrationPattern)value;

/*!
 * @brief Retrieves an array with all VibrationPatterns wrapped in IDRVibrationPatternWrapper objects
 * @return NSArray with all VibrationPatterns wrapped in IDRVibrationPatternWrapper objects
 */
+(nonnull NSArray<IDRVibrationPatternWrapper *> *) allVibrationPatterns;

@end
