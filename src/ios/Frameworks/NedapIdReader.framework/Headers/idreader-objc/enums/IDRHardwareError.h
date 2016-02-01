#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief A HardwareError is reported when something went wrong because of the hardware.
 */
typedef NS_ENUM(uint8_t, IDRHardwareError) {
    IDRHardwareErrorNotAvailable = 0, ///< Hardware not available
    IDRHardwareErrorStoreFailed = 1, ///< Flash store failed
    IDRHardwareErrorSyncTimeout = 2, ///< Sync timeout
    IDRHardwareErrorTransceiverError = 3, ///< Transceiver error
    IDRHardwareErrorRfidNotConnected = 4, ///< RFID transceiver not connected
    IDRHardwareErrorBarcodeReaderNotConnected = 5, ///< Barcode reader not connected
};

/*! 
 * @brief A HardwareError is reported when something went wrong because of the hardware.
 */
@interface IDRHardwareErrorWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRHardwareError enumeration value.
 * @param enumValue The IDRHardwareError value.
 * @return IDRHardwareError instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRHardwareError)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRHardwareError value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRHardwareError value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRHardwareError value;

/*!
 * @brief Creates a wrapped object with a IDRHardwareError enumeration value.
 * @param value The IDRHardwareError value.
 * @return IDRHardwareError instance representing the enum value.
 */
+(nonnull instancetype) hardwareErrorWrapperWithValue:(IDRHardwareError)value;

/*!
 * @brief Retrieves an array with all HardwareErrors wrapped in IDRHardwareErrorWrapper objects
 * @return NSArray with all HardwareErrors wrapped in IDRHardwareErrorWrapper objects
 */
+(nonnull NSArray<IDRHardwareErrorWrapper *> *) allHardwareErrors;

@end
