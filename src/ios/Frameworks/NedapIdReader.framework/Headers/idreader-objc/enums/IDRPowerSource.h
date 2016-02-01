#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief Power source enumeration
 */
typedef NS_ENUM(uint8_t, IDRPowerSource) {
    IDRPowerSourceBattery = 0, ///< Battery powered
    IDRPowerSourceUSB = 1, ///< USB powered
    IDRPowerSourceWireless = 2, ///< Wireless (Qi) powered
};

/*! 
 * @brief Power source enumeration
 */
@interface IDRPowerSourceWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRPowerSource enumeration value.
 * @param enumValue The IDRPowerSource value.
 * @return IDRPowerSource instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRPowerSource)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRPowerSource value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRPowerSource value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRPowerSource value;

/*!
 * @brief Creates a wrapped object with a IDRPowerSource enumeration value.
 * @param value The IDRPowerSource value.
 * @return IDRPowerSource instance representing the enum value.
 */
+(nonnull instancetype) powerSourceWrapperWithValue:(IDRPowerSource)value;

/*!
 * @brief Retrieves an array with all PowerSources wrapped in IDRPowerSourceWrapper objects
 * @return NSArray with all PowerSources wrapped in IDRPowerSourceWrapper objects
 */
+(nonnull NSArray<IDRPowerSourceWrapper *> *) allPowerSources;

@end
