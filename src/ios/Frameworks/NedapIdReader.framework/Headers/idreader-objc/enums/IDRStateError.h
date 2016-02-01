#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief A StateError is reported when a command is sent, while this is not expected in the current state.
 */
typedef NS_ENUM(uint8_t, IDRStateError) {
    IDRStateErrorRfidBusy = 0, ///< RFID is busy (end the current RFID action first)
    IDRStateErrorAlreadyStopped = 1, ///< RFID is already stopped (stop command while RFID was not running)
    IDRStateErrorIncorrectFirmwareCrc = 2, ///< CRC of firmware is incorrect
    IDRStateErrorNoBeamSteeringPeripheralConnected = 3, ///< No beam steering peripheral is connected
    IDRStateErrorTransceiverFirmwareUpdateTimeout = 4, ///< Timeout for transceiver firmware update
    IDRStateErrorTransceiverFirmwareUpdateNotCompleted = 5, ///< Transceiver firmware update not completed
    IDRStateErrorNotInTransceiverFirmwareUpdateMode = 6, ///< Not in transceiver firmware update mode
    IDRStateErrorFirmwareUpdateIncorrectOrder = 7, ///< Incorrect order of firmware update packets
    IDRStateErrorIncorrectFirmwareSignature = 8, ///< Incorrect signature for firmware update binary
    IDRStateErrorBarcodeReaderBusy = 9, ///< Barcode reader is busy
    IDRStateErrorUserFeedbackBusy = 10, ///< User feedback is busy
    IDRStateErrorInvalidState = 255, ///< Invalid state
};

/*! 
 * @brief A StateError is reported when a command is sent, while this is not expected in the current state.
 */
@interface IDRStateErrorWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRStateError enumeration value.
 * @param enumValue The IDRStateError value.
 * @return IDRStateError instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRStateError)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRStateError value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRStateError value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRStateError value;

/*!
 * @brief Creates a wrapped object with a IDRStateError enumeration value.
 * @param value The IDRStateError value.
 * @return IDRStateError instance representing the enum value.
 */
+(nonnull instancetype) stateErrorWrapperWithValue:(IDRStateError)value;

/*!
 * @brief Retrieves an array with all StateErrors wrapped in IDRStateErrorWrapper objects
 * @return NSArray with all StateErrors wrapped in IDRStateErrorWrapper objects
 */
+(nonnull NSArray<IDRStateErrorWrapper *> *) allStateErrors;

@end
