#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief LED mode
 */
typedef NS_ENUM(uint8_t, IDRLedMode) {
    IDRLedModeOff = 0, ///< LED off
    IDRLedModeOn = 1, ///< LED on
    IDRLedModeBlinking = 2, ///< LED blinking
};

/*! 
 * @brief LED mode
 */
@interface IDRLedModeWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRLedMode enumeration value.
 * @param enumValue The IDRLedMode value.
 * @return IDRLedMode instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRLedMode)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRLedMode value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRLedMode value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRLedMode value;

/*!
 * @brief Creates a wrapped object with a IDRLedMode enumeration value.
 * @param value The IDRLedMode value.
 * @return IDRLedMode instance representing the enum value.
 */
+(nonnull instancetype) ledModeWrapperWithValue:(IDRLedMode)value;

/*!
 * @brief Retrieves an array with all LedModes wrapped in IDRLedModeWrapper objects
 * @return NSArray with all LedModes wrapped in IDRLedModeWrapper objects
 */
+(nonnull NSArray<IDRLedModeWrapper *> *) allLedModes;

@end
