#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"

#include "IDRClassDeclarations.h"

/*! 
 * @brief Packet class. Every packet is inherited from this class.
 */
@interface IDRPacket : NSObject

/*! 
 * @brief Gets the command ID of the packet.
 * @return Command ID
 */
- (uint8_t)commandId;

/*! 
 * @brief Gets the name of the packet.
 * @return Packet name
 */
- (nonnull NSString *)name;

/*! 
 * @brief Gets the prefix of the packet.
 * @return Packet prefix
 */
- (uint8_t)prefix;

/*! 
 * @brief Gets a string representation of this packet, suitable for logging purposes.
 * @return String representation of this packet
 */
- (nonnull NSString *)toString;

/*! 
 * @brief Gets the raw data of this packet.
 * @return Byte array with raw packet data
 */
- (nonnull NSData *)packetData;

/*! 
 * @brief Gets the command ID of the packet.
 * @return Command ID
 */
@property(nonatomic, readonly, getter=commandId) uint8_t commandId;

/*! 
 * @brief Gets the name of the packet.
 * @return Packet name
 */
@property(nonatomic, nonnull, readonly, getter=name) NSString * name;

/*! 
 * @brief Gets the prefix of the packet.
 * @return Packet prefix
 */
@property(nonatomic, readonly, getter=prefix) uint8_t prefix;

/*! 
 * @brief Gets the raw data of this packet.
 * @return Byte array with raw packet data
 */
@property(nonatomic, nonnull, readonly, getter=packetData) NSData * packetData;

+ (nonnull IDRPacket *)deserializeWithData:(nonnull NSData *) data;

+ (nonnull NSArray<NSNumber *> *)registeredPacketCommandIds;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;


@end
