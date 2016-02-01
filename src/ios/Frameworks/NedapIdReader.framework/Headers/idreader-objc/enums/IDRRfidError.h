#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief An RfidError is reported when something has gone wrong with the connected RFID antenna or environment.
 */
typedef NS_ENUM(uint8_t, IDRRfidError) {
    IDRRfidErrorAntennaMismatch = 0, ///< The reflected power is too high (check antenna and environment)
    IDRRfidErrorPowerError = 1, ///< The reader could not settle its output power (check antenna and environment)
};

/*! 
 * @brief An RfidError is reported when something has gone wrong with the connected RFID antenna or environment.
 */
@interface IDRRfidErrorWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRRfidError enumeration value.
 * @param enumValue The IDRRfidError value.
 * @return IDRRfidError instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRRfidError)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRRfidError value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRRfidError value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRRfidError value;

/*!
 * @brief Creates a wrapped object with a IDRRfidError enumeration value.
 * @param value The IDRRfidError value.
 * @return IDRRfidError instance representing the enum value.
 */
+(nonnull instancetype) rfidErrorWrapperWithValue:(IDRRfidError)value;

/*!
 * @brief Retrieves an array with all RfidErrors wrapped in IDRRfidErrorWrapper objects
 * @return NSArray with all RfidErrors wrapped in IDRRfidErrorWrapper objects
 */
+(nonnull NSArray<IDRRfidErrorWrapper *> *) allRfidErrors;

@end
