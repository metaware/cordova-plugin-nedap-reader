#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief An OtherError is reported when something internally went wrong in the RFID transceiver.
 *
 * In case of problems, please contact Nedap with the toString description of the error packet and steps how to reproduce.
 */
typedef NS_ENUM(uint8_t, IDROtherError) {
    IDROtherErrorImpinj = 0, ///< RFID transceiver error
};

/*! 
 * @brief An OtherError is reported when something internally went wrong in the RFID transceiver.
 *
 * In case of problems, please contact Nedap with the toString description of the error packet and steps how to reproduce.
 */
@interface IDROtherErrorWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDROtherError enumeration value.
 * @param enumValue The IDROtherError value.
 * @return IDROtherError instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDROtherError)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDROtherError value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDROtherError value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDROtherError value;

/*!
 * @brief Creates a wrapped object with a IDROtherError enumeration value.
 * @param value The IDROtherError value.
 * @return IDROtherError instance representing the enum value.
 */
+(nonnull instancetype) otherErrorWrapperWithValue:(IDROtherError)value;

/*!
 * @brief Retrieves an array with all OtherErrors wrapped in IDROtherErrorWrapper objects
 * @return NSArray with all OtherErrors wrapped in IDROtherErrorWrapper objects
 */
+(nonnull NSArray<IDROtherErrorWrapper *> *) allOtherErrors;

@end
