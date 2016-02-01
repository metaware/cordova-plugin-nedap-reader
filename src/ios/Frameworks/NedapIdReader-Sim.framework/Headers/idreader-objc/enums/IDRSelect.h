#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief Status of the EPC Gen2 Select flag
 */
typedef NS_ENUM(uint8_t, IDRSelect) {
    IDRSelectAny = 0, ///< Tags will respond regardless of the SL flag status
    IDRSelectDeasserted = 2, ///< Only tags having SL deasserted will respond
    IDRSelectAsserted = 3, ///< Only tags having SL asserted will respond
};

/*! 
 * @brief Status of the EPC Gen2 Select flag
 */
@interface IDRSelectWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRSelect enumeration value.
 * @param enumValue The IDRSelect value.
 * @return IDRSelect instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRSelect)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRSelect value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRSelect value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRSelect value;

/*!
 * @brief Creates a wrapped object with a IDRSelect enumeration value.
 * @param value The IDRSelect value.
 * @return IDRSelect instance representing the enum value.
 */
+(nonnull instancetype) selectWrapperWithValue:(IDRSelect)value;

/*!
 * @brief Retrieves an array with all Selects wrapped in IDRSelectWrapper objects
 * @return NSArray with all Selects wrapped in IDRSelectWrapper objects
 */
+(nonnull NSArray<IDRSelectWrapper *> *) allSelects;

@end
