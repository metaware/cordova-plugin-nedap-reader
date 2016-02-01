#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRSendablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief Command to send a chunk of firmware data to the reader. The reader will respond with a StoreFirmwareBlockCompleted response.
 *
 * To perform a firmware update, the firmware binary needs to be split up into 256-byte chunks (last chunck may be smaller).
 * Each chunk needs to be sent to the reader using the StoreFirmwareBlock command. The packet number indicates the position
 * of the firmware data (e.g. packet number 0 means bytes 0..255, packet number 1 means bytes 256..511, etc.).
 * After having sent all chunks of firmware data, execute the firmware update using the StartFirmwareUpgrade command.
 */
@interface IDRStoreFirmwareBlockPacket : IDRSendablePacket

/*! 
 * @brief Constructs a StoreFirmwareBlockPacket.
 * @param packetNumber The chunk number of the provided data, which indicates the offset in the binary file (offset = 256 * packetNumber)
 * @param data Pointer to the firmware data
 * @param dataLength Length of this chunk. Every chunk is 256 bytes, except for the last chunk, which may be smaller.
 */
- (nonnull instancetype)initWithPacketNumber:(uint16_t)packetNumber data:(nonnull byte *)data dataLength:(uint32_t)dataLength;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a StoreFirmwareBlockPacket.
 * @param packetNumber The chunk number of the provided data, which indicates the offset in the binary file (offset = 256 * packetNumber)
 * @param data Pointer to the firmware data
 * @param dataLength Length of this chunk. Every chunk is 256 bytes, except for the last chunk, which may be smaller.
 */
+ (nonnull instancetype)packetWithPacketNumber:(uint16_t)packetNumber data:(nonnull byte *)data dataLength:(uint32_t)dataLength;


@end
