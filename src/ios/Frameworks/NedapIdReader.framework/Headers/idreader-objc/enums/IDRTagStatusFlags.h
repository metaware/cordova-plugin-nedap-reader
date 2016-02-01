#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief Tag status flags
 */
typedef NS_OPTIONS(uint8_t, IDRTagStatusFlags) {
    IDRTagStatusFlagsNone = 0, ///< None
    IDRTagStatusFlagsMuted = 1, ///< Tag is muted
};

/*! 
 * @brief Tag status flags
 */
@interface IDRTagStatusFlagsWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRTagStatusFlags enumeration value.
 * @param enumValue The IDRTagStatusFlags value.
 * @return IDRTagStatusFlags instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRTagStatusFlags)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRTagStatusFlags value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRTagStatusFlags value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRTagStatusFlags value;

/*!
 * @brief Creates a wrapped object with a IDRTagStatusFlags enumeration value.
 * @param value The IDRTagStatusFlags value.
 * @return IDRTagStatusFlags instance representing the enum value.
 */
+(nonnull instancetype) tagStatusFlagsWrapperWithValue:(IDRTagStatusFlags)value;

/*!
 * @brief Retrieves an array with all TagStatusFlags wrapped in IDRTagStatusFlagsWrapper objects
 * @return NSArray with all TagStatusFlags wrapped in IDRTagStatusFlagsWrapper objects
 */
+(nonnull NSArray<IDRTagStatusFlagsWrapper *> *) allTagStatusFlags;

@end
