#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRReceivablePacket.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief The Regulation packet contains the current configured regulation and the regulations supported by the reader.
 */
@interface IDRRegulationPacket : IDRReceivablePacket

/*! 
 * @brief Constructs a Regulation packet with received packet data.
 * @param data Raw packet data
 */
- (nonnull instancetype)initWithData:(nonnull NSData *)data;

/*! 
 * @brief Gets a string representation of this packet, suitable for logging purposes.
 * @return String representation of this packet.
 */
- (nonnull NSString *)toString;

/*! 
 * @brief Get the current configured regulation as reported by the reader.
 * @return The current configured regulation.
 */
- (IDRRegulation)regulation;

/*! 
 * @brief Retrieves the list of supported regulations as reported by the reader.
 * @return An array of supported regulations.
 */
- (nonnull NSArray<IDRRegulationWrapper *> *)supportedRegulations;

/*! 
 * @brief Get the current configured regulation as reported by the reader.
 * @return The current configured regulation.
 */
@property(nonatomic, readonly, getter=regulation) IDRRegulation regulation;

/*! 
 * @brief Retrieves the list of supported regulations as reported by the reader.
 * @return An array of supported regulations.
 */
@property(nonatomic, nonnull, readonly, getter=supportedRegulations) NSArray<IDRRegulationWrapper *> * supportedRegulations;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)packetWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a Regulation packet with received packet data.
 * @param data Raw packet data
 */
+ (nonnull instancetype)packetWithData:(nonnull NSData *)data;


@end
