#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief A ProtocolError is reported when an invalid command is sent.
 */
typedef NS_ENUM(uint8_t, IDRProtocolError) {
    IDRProtocolErrorUnknownCommand = 0, ///< Command is unknown for this reader (check firmware version and whether this device supports the command)
    IDRProtocolErrorInvalidData = 1, ///< Packet data in the command is invalid
    IDRProtocolErrorInvalidCrc = 2, ///< Packet CRC is invalid
    IDRProtocolErrorInvalidStandAloneCommand = 3, ///< Standalone command is invalid
    IDRProtocolErrorInvalidBarcodeReaderCommand = 4, ///< Barcode reader command is invalid
    IDRProtocolErrorInvalidUserFeedbackCommand = 5, ///< User feedback command is invalid
};

/*! 
 * @brief A ProtocolError is reported when an invalid command is sent.
 */
@interface IDRProtocolErrorWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRProtocolError enumeration value.
 * @param enumValue The IDRProtocolError value.
 * @return IDRProtocolError instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRProtocolError)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRProtocolError value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRProtocolError value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRProtocolError value;

/*!
 * @brief Creates a wrapped object with a IDRProtocolError enumeration value.
 * @param value The IDRProtocolError value.
 * @return IDRProtocolError instance representing the enum value.
 */
+(nonnull instancetype) protocolErrorWrapperWithValue:(IDRProtocolError)value;

/*!
 * @brief Retrieves an array with all ProtocolErrors wrapped in IDRProtocolErrorWrapper objects
 * @return NSArray with all ProtocolErrors wrapped in IDRProtocolErrorWrapper objects
 */
+(nonnull NSArray<IDRProtocolErrorWrapper *> *) allProtocolErrors;

@end
