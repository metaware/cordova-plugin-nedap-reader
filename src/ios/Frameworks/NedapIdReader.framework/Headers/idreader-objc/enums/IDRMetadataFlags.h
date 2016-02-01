#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief Metadata flags used in observations
 */
typedef NS_OPTIONS(uint16_t, IDRMetadataFlags) {
    IDRMetadataFlagsNone = 0, ///< None
    IDRMetadataFlagsRssi = 1, ///< Received signal strength indicator (RSSI)
    IDRMetadataFlagsFrequency = 2, ///< Frequency
    IDRMetadataFlagsPhase = 4, ///< Phase
    IDRMetadataFlagsAntenna = 8, ///< Transmit and receive antenna
    IDRMetadataFlagsTimestamp = 16, ///< Timestamp
    IDRMetadataFlagsBeamId = 32, ///< Beam ID
    IDRMetadataFlagsEpcCrc = 256, ///< EPC CRC
    IDRMetadataFlagsEpcPc = 512, ///< EPC PC
    IDRMetadataFlagsMotion = 1024, ///< Tag motion
    IDRMetadataFlagsTagStatus = 2048, ///< Tag status
};

/*! 
 * @brief Metadata flags used in observations
 */
@interface IDRMetadataFlagsWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRMetadataFlags enumeration value.
 * @param enumValue The IDRMetadataFlags value.
 * @return IDRMetadataFlags instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRMetadataFlags)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRMetadataFlags value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRMetadataFlags value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRMetadataFlags value;

/*!
 * @brief Creates a wrapped object with a IDRMetadataFlags enumeration value.
 * @param value The IDRMetadataFlags value.
 * @return IDRMetadataFlags instance representing the enum value.
 */
+(nonnull instancetype) metadataFlagsWrapperWithValue:(IDRMetadataFlags)value;

/*!
 * @brief Retrieves an array with all MetadataFlags wrapped in IDRMetadataFlagsWrapper objects
 * @return NSArray with all MetadataFlags wrapped in IDRMetadataFlagsWrapper objects
 */
+(nonnull NSArray<IDRMetadataFlagsWrapper *> *) allMetadataFlags;

@end
