#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief Which source to use for conversion from GTIN to SGTIN
 */
typedef NS_ENUM(uint8_t, IDRSerializationSource) {
    IDRSerializationSourceSupplied = 1, ///< Serial is supplied
    IDRSerializationSourceInvalid = 255, ///< Invalid
};

/*! 
 * @brief Which source to use for conversion from GTIN to SGTIN
 */
@interface IDRSerializationSourceWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRSerializationSource enumeration value.
 * @param enumValue The IDRSerializationSource value.
 * @return IDRSerializationSource instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRSerializationSource)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRSerializationSource value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRSerializationSource value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRSerializationSource value;

/*!
 * @brief Creates a wrapped object with a IDRSerializationSource enumeration value.
 * @param value The IDRSerializationSource value.
 * @return IDRSerializationSource instance representing the enum value.
 */
+(nonnull instancetype) serializationSourceWrapperWithValue:(IDRSerializationSource)value;

/*!
 * @brief Retrieves an array with all SerializationSources wrapped in IDRSerializationSourceWrapper objects
 * @return NSArray with all SerializationSources wrapped in IDRSerializationSourceWrapper objects
 */
+(nonnull NSArray<IDRSerializationSourceWrapper *> *) allSerializationSources;

@end
