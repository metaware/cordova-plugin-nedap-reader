#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief EPC Gen2 Target
 */
typedef NS_ENUM(uint8_t, IDRTarget) {
    IDRTargetA = 0, ///< Only tags in target A will respond (without autoflip), or start query in target B (with autoflip)
    IDRTargetB = 1, ///< Only tags in target B will respond (without autoflip), or start query in target A (with autoflip)
};

/*! 
 * @brief EPC Gen2 Target
 */
@interface IDRTargetWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRTarget enumeration value.
 * @param enumValue The IDRTarget value.
 * @return IDRTarget instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRTarget)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRTarget value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRTarget value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRTarget value;

/*!
 * @brief Creates a wrapped object with a IDRTarget enumeration value.
 * @param value The IDRTarget value.
 * @return IDRTarget instance representing the enum value.
 */
+(nonnull instancetype) targetWrapperWithValue:(IDRTarget)value;

/*!
 * @brief Retrieves an array with all Targets wrapped in IDRTargetWrapper objects
 * @return NSArray with all Targets wrapped in IDRTargetWrapper objects
 */
+(nonnull NSArray<IDRTargetWrapper *> *) allTargets;

@end
