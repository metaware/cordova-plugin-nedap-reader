#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRSendablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief Command to stop the barcode reader. The reader will respond with a BarcodeReaderStopped response.
 */
@interface IDRStopBarcodeReaderPacket : IDRSendablePacket

/*! 
 * @brief Constructs a StopBarcodeReaderPacket command
 */
- (nonnull instancetype)init;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a StopBarcodeReaderPacket command
 */
+ (nonnull instancetype)packet;


@end
