#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRReceivablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief An InventoryObservation is received when one or more RFID tags have been queried successfully. It contains the EPC(s) and additional metadata.
 */
@interface IDRInventoryObservationPacket : IDRReceivablePacket

/*! 
 * @brief Constructs an InventoryObservation packet from raw received data
 * @param data Byte array with data
 */
- (nonnull instancetype)initWithData:(nonnull NSData *)data;

/*! 
 * @brief Gets a string representation of this packet, suitable for logging purposes.
 * @return String representation of this packet.
 */
- (nonnull NSString *)toString;

/*! 
 * @brief Gets the set of metadata flags that are included in the inventory observation(s)
 * @return Bitmask with metadata flags
 */
- (IDRMetadataFlags)metadataFlags;

/*! 
 * @brief Gets the array of individual observations
 * 
 * @see Observation
 * 
 * @return Array with observations
 */
- (nonnull NSArray<IDRObservation *> *)observations;

/*! 
 * @brief Gets the set of metadata flags that are included in the inventory observation(s)
 * @return Bitmask with metadata flags
 */
@property(nonatomic, readonly, getter=metadataFlags) IDRMetadataFlags metadataFlags;

/*! 
 * @brief Gets the array of individual observations
 * 
 * @see Observation
 * 
 * @return Array with observations
 */
@property(nonatomic, nonnull, readonly, getter=observations) NSArray<IDRObservation *> * observations;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs an InventoryObservation packet from raw received data
 * @param data Byte array with data
 */
+ (nonnull instancetype)packetWithData:(nonnull NSData *)data;


@end
