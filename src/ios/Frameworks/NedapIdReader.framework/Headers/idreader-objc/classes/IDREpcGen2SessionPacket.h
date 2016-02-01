#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRReceivablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief The EpcGen2Session packet contains the current configured EPC Gen2 session parameters.
 */
@interface IDREpcGen2SessionPacket : IDRReceivablePacket

/*! 
 * @brief Constructs an EpcGen2Session packet from raw received data
 * @param data Byte array with data
 */
- (nonnull instancetype)initWithData:(nonnull NSData *)data;

/*! 
 * @brief Gets a string representation of this packet, suitable for logging purposes.
 * @return String representation of this packet.
 */
- (nonnull NSString *)toString;

/*! 
 * @brief Gets the configured EPC Gen2 session.
 * @return EPC Gen2 session
 */
- (IDRSession)session;

/*! 
 * @brief Gets the configured EPC Gen2 target.
 * @return EPC Gen2 target
 */
- (IDRTarget)target;

/*! 
 * @brief Gets the configured EPC Gen2 select.
 * @return EPC Gen2 select
 */
- (IDRSelect)select;

/*! 
 * @brief Gets the configured auto-flip parameter.
 *
 * The auto-flip parameter indicates after how many query rounds the reader should switch to the other target. If
 * set to 0, auto-flipping is disabled.
 * 
 * @return After how many query rounds the target is flipped, or 0 for no target flipping.
 */
- (uint8_t)autoFlip;

/*! 
 * @brief Gets the configured EPC Gen2 session.
 * @return EPC Gen2 session
 */
@property(nonatomic, readonly, getter=session) IDRSession session;

/*! 
 * @brief Gets the configured EPC Gen2 target.
 * @return EPC Gen2 target
 */
@property(nonatomic, readonly, getter=target) IDRTarget target;

/*! 
 * @brief Gets the configured EPC Gen2 select.
 * @return EPC Gen2 select
 */
@property(nonatomic, readonly, getter=select) IDRSelect select;

/*! 
 * @brief Gets the configured auto-flip parameter.
 *
 * The auto-flip parameter indicates after how many query rounds the reader should switch to the other target. If
 * set to 0, auto-flipping is disabled.
 * 
 * @return After how many query rounds the target is flipped, or 0 for no target flipping.
 */
@property(nonatomic, readonly, getter=autoFlip) uint8_t autoFlip;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs an EpcGen2Session packet from raw received data
 * @param data Byte array with data
 */
+ (nonnull instancetype)packetWithData:(nonnull NSData *)data;


@end
