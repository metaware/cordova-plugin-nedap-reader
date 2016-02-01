#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief A configuration error is reported when some configuration is invalid.
 */
typedef NS_ENUM(uint8_t, IDRConfigurationError) {
    IDRConfigurationErrorNoRegulationSelected = 0, ///< No regulation selected
    IDRConfigurationErrorNoStrategyConfigured = 1, ///< No strategy configured
    IDRConfigurationErrorInvalidFrequencyChannel = 2, ///< Invalid frequency channel
    IDRConfigurationErrorNotAllFrequencyChannelsUsed = 3, ///< Not all frequency channels used, while this is obligatory by the regulation
    IDRConfigurationErrorBeamNotSupported = 4, ///< Beam not supported
    IDRConfigurationErrorAntennaNotSupported = 5, ///< Antenna configuration not supported
};

/*! 
 * @brief A configuration error is reported when some configuration is invalid.
 */
@interface IDRConfigurationErrorWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRConfigurationError enumeration value.
 * @param enumValue The IDRConfigurationError value.
 * @return IDRConfigurationError instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRConfigurationError)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRConfigurationError value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRConfigurationError value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRConfigurationError value;

/*!
 * @brief Creates a wrapped object with a IDRConfigurationError enumeration value.
 * @param value The IDRConfigurationError value.
 * @return IDRConfigurationError instance representing the enum value.
 */
+(nonnull instancetype) configurationErrorWrapperWithValue:(IDRConfigurationError)value;

/*!
 * @brief Retrieves an array with all ConfigurationErrors wrapped in IDRConfigurationErrorWrapper objects
 * @return NSArray with all ConfigurationErrors wrapped in IDRConfigurationErrorWrapper objects
 */
+(nonnull NSArray<IDRConfigurationErrorWrapper *> *) allConfigurationErrors;

@end
