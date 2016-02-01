#pragma once

#include "util/IDRCommon.h"

#import "classes/IDRPacket.h"

@class IDRPacketParser;

/*!
 * @brief The delegate for the packet parser. For internal API usage only.
 */
@protocol IDRPacketParserDelegate
@required

/*!
 * @brief Called when a complete packet is received by the packet parser.
 * @param packetParser The packet parser which received a packet
 * @param packet The received packet
 */
- (void)packetParser:(nonnull IDRPacketParser *)packetParser didReceivePacket:(nonnull IDRPacket *)packet;

@end

/**
 * @brief The PacketParser can be used to convert raw received bytes to packets.
 */
@interface IDRPacketParser : NSObject {
}

/*!
 * @brief Delegate to report complete packets to.
 */
@property(weak, nullable) id<IDRPacketParserDelegate> delegate;

/*!
 * @brief Call this when data is received from the reader.
 * @param data Received data
 */
- (void)write:(nonnull NSData *)data;

@end
