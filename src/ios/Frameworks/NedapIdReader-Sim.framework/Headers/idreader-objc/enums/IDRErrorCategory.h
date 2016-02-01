#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief The error category
 */
typedef NS_ENUM(uint8_t, IDRErrorCategory) {
    IDRErrorCategoryProtocol = 0, ///< Protocol error
    IDRErrorCategoryState = 1, ///< State error
    IDRErrorCategoryConfiguration = 2, ///< Configuration error
    IDRErrorCategoryHardware = 3, ///< Hardware error
    IDRErrorCategoryRfid = 4, ///< Rfid error
    IDRErrorCategoryOther = 5, ///< Other error
};

/*! 
 * @brief The error category
 */
@interface IDRErrorCategoryWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRErrorCategory enumeration value.
 * @param enumValue The IDRErrorCategory value.
 * @return IDRErrorCategory instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRErrorCategory)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRErrorCategory value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRErrorCategory value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRErrorCategory value;

/*!
 * @brief Creates a wrapped object with a IDRErrorCategory enumeration value.
 * @param value The IDRErrorCategory value.
 * @return IDRErrorCategory instance representing the enum value.
 */
+(nonnull instancetype) errorCategoryWrapperWithValue:(IDRErrorCategory)value;

/*!
 * @brief Retrieves an array with all ErrorCategorys wrapped in IDRErrorCategoryWrapper objects
 * @return NSArray with all ErrorCategorys wrapped in IDRErrorCategoryWrapper objects
 */
+(nonnull NSArray<IDRErrorCategoryWrapper *> *) allErrorCategorys;

@end
