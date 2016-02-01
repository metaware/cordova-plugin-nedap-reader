#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief EPC Gen2 Session
 */
typedef NS_ENUM(uint8_t, IDRSession) {
    IDRSessionS0 = 0, ///< Session 0
    IDRSessionS1 = 1, ///< Session 1
    IDRSessionS2 = 2, ///< Session 2
    IDRSessionS3 = 3, ///< Session 3
};

/*! 
 * @brief EPC Gen2 Session
 */
@interface IDRSessionWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRSession enumeration value.
 * @param enumValue The IDRSession value.
 * @return IDRSession instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRSession)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRSession value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRSession value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRSession value;

/*!
 * @brief Creates a wrapped object with a IDRSession enumeration value.
 * @param value The IDRSession value.
 * @return IDRSession instance representing the enum value.
 */
+(nonnull instancetype) sessionWrapperWithValue:(IDRSession)value;

/*!
 * @brief Retrieves an array with all Sessions wrapped in IDRSessionWrapper objects
 * @return NSArray with all Sessions wrapped in IDRSessionWrapper objects
 */
+(nonnull NSArray<IDRSessionWrapper *> *) allSessions;

@end
