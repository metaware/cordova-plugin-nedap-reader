#pragma once

#include "../util/IDRCommon.h"

/*!
 * Button event type
 */
typedef NS_ENUM(uint8_t, IDRButtonEventType) {
    IDRButtonEventTypeDown = 0, ///< Button is pressed
    IDRButtonEventTypeUp = 1, ///< Button is released
};

/*!
 * Button event type
 */
@interface IDRButtonEventTypeWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRButtonEventType enumeration value.
 * @param enumValue The IDRButtonEventType value.
 * @return IDRButtonEventType instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRButtonEventType)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRButtonEventType value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRButtonEventType value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRButtonEventType value;

/*!
 * @brief Creates a wrapped object with a IDRButtonEventType enumeration value.
 * @param value The IDRButtonEventType value.
 * @return IDRButtonEventType instance representing the enum value.
 */
+(nonnull instancetype) buttonEventTypeWrapperWithValue:(IDRButtonEventType)value;

/*!
 * @brief Retrieves an array with all ButtonEventTypes wrapped in IDRButtonEventTypeWrapper objects
 * @return NSArray with all ButtonEventTypes wrapped in IDRButtonEventTypeWrapper objects
 */
+(nonnull NSArray<IDRButtonEventTypeWrapper *> *) allButtonEventTypes;

@end
