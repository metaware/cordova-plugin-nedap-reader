#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRSendablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief Command to start the firmware upgrade. The reader will disconnect and reboot if successful.
 *
 * After having sent all firmware data to the reader, perform this command to actually execute the firmware ugrade.
 */
@interface IDRStartFirmwareUpgradePacket : IDRSendablePacket

/*! 
 * @brief Constructs a StartFirmwareUpgrade packet
 * @param totalSize The total size of the binary in bytes
 * @param crc The CRC-32 calculated over the complete binary. This is used to check if the complete binary has been received correctly.
 */
- (nonnull instancetype)initWithTotalSize:(uint32_t)totalSize crc:(uint32_t)crc;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a StartFirmwareUpgrade packet
 * @param totalSize The total size of the binary in bytes
 * @param crc The CRC-32 calculated over the complete binary. This is used to check if the complete binary has been received correctly.
 */
+ (nonnull instancetype)packetWithTotalSize:(uint32_t)totalSize crc:(uint32_t)crc;


@end
