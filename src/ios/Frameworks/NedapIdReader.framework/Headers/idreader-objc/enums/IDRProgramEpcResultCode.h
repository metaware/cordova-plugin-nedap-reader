#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief Result code for a 'Program EPC' action
 */
typedef NS_ENUM(uint8_t, IDRProgramEpcResultCode) {
    IDRProgramEpcResultCodeSuccess = 0, ///< Label successfully programmed and verified
    IDRProgramEpcResultCodeNoLabel = 1, ///< Could not find a label to program the EPC of (reported TID and EPC fields will be empty)
    IDRProgramEpcResultCodeMultipleLabels = 2, ///< Multiple labels in range (reported TID and EPC fields will be empty)
    IDRProgramEpcResultCodeNoXtid = 3, ///< Label has no XTID, while serialization source is set to use XTID
    IDRProgramEpcResultCodeInvalidSerial = 4, ///< Invalid serial number supplied
    IDRProgramEpcResultCodeUnsupportedLabel = 5, ///< Unsupported label type
    IDRProgramEpcResultCodeWriteFailed = 6, ///< Writing the EPC failed (EPC might be partially programmed)
    IDRProgramEpcResultCodeVerifyFailed = 7, ///< Verification of the EPC failed (EPC might be partially programmed)
    IDRProgramEpcResultCodeLabelLost = 8, ///< Communication with the label was lost during programming (reported TID might be incomplete)
    IDRProgramEpcResultCodeMemoryLocked = 9, ///< EPC bank in the label is locked or password protected
    IDRProgramEpcResultCodeSerialisationFailed = 10, ///< Conversion from GTIN to SGTIN failed
};

/*! 
 * @brief Result code for a 'Program EPC' action
 */
@interface IDRProgramEpcResultCodeWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRProgramEpcResultCode enumeration value.
 * @param enumValue The IDRProgramEpcResultCode value.
 * @return IDRProgramEpcResultCode instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRProgramEpcResultCode)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRProgramEpcResultCode value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRProgramEpcResultCode value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRProgramEpcResultCode value;

/*!
 * @brief Creates a wrapped object with a IDRProgramEpcResultCode enumeration value.
 * @param value The IDRProgramEpcResultCode value.
 * @return IDRProgramEpcResultCode instance representing the enum value.
 */
+(nonnull instancetype) programEpcResultCodeWrapperWithValue:(IDRProgramEpcResultCode)value;

/*!
 * @brief Retrieves an array with all ProgramEpcResultCodes wrapped in IDRProgramEpcResultCodeWrapper objects
 * @return NSArray with all ProgramEpcResultCodes wrapped in IDRProgramEpcResultCodeWrapper objects
 */
+(nonnull NSArray<IDRProgramEpcResultCodeWrapper *> *) allProgramEpcResultCodes;

@end
