#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief Antenna type
 */
typedef NS_ENUM(uint8_t, IDRAntenna) {
    IDRAntennaNone = 0, ///< No antenna
    IDRAntennaLocalNextAntenna = 16, ///< Local next antenna
    IDRAntennaLocalPrevAntenna = 17, ///< Local prev antenna
    IDRAntennaRemoteNextPort = 48, ///< Remote next port
    IDRAntennaRemotePrevPort = 32, ///< Remote prev port
};

/*! 
 * @brief Antenna type
 */
@interface IDRAntennaWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRAntenna enumeration value.
 * @param enumValue The IDRAntenna value.
 * @return IDRAntenna instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRAntenna)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRAntenna value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRAntenna value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRAntenna value;

/*!
 * @brief Creates a wrapped object with a IDRAntenna enumeration value.
 * @param value The IDRAntenna value.
 * @return IDRAntenna instance representing the enum value.
 */
+(nonnull instancetype) antennaWrapperWithValue:(IDRAntenna)value;

/*!
 * @brief Retrieves an array with all Antennas wrapped in IDRAntennaWrapper objects
 * @return NSArray with all Antennas wrapped in IDRAntennaWrapper objects
 */
+(nonnull NSArray<IDRAntennaWrapper *> *) allAntennas;

@end
