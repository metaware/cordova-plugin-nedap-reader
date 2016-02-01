#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief Method of EPC encoding
 */
typedef NS_ENUM(uint8_t, IDREpcEncoding) {
    IDREpcEncodingRawEpc = 0, ///< Raw EPC (provided)
    IDREpcEncodingSgtin96 = 1, ///< Serialized global trade item number (SGTIN-96)
    IDREpcEncodingSgtin198 = 2, ///< Serialized global trade item number (SGTIN-198)
    IDREpcEncodingInvalid = 255, ///< Invalid
};

/*! 
 * @brief Method of EPC encoding
 */
@interface IDREpcEncodingWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDREpcEncoding enumeration value.
 * @param enumValue The IDREpcEncoding value.
 * @return IDREpcEncoding instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDREpcEncoding)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDREpcEncoding value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDREpcEncoding value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDREpcEncoding value;

/*!
 * @brief Creates a wrapped object with a IDREpcEncoding enumeration value.
 * @param value The IDREpcEncoding value.
 * @return IDREpcEncoding instance representing the enum value.
 */
+(nonnull instancetype) epcEncodingWrapperWithValue:(IDREpcEncoding)value;

/*!
 * @brief Retrieves an array with all EpcEncodings wrapped in IDREpcEncodingWrapper objects
 * @return NSArray with all EpcEncodings wrapped in IDREpcEncodingWrapper objects
 */
+(nonnull NSArray<IDREpcEncodingWrapper *> *) allEpcEncodings;

@end
