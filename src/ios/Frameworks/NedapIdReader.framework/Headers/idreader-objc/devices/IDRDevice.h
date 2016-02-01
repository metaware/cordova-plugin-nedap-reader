#pragma once

#import "../IDRPacketParser.h"
#import "../IDRDeviceListener.h"

/*!
 * @brief Represents a connection with a reader.
 */
@interface IDRDevice : NSObject <IDRPacketParserDelegate> {
    dispatch_queue_t serialQueue;
}

/*!
 * @brief The packet reader
 */
@property(nonatomic, nonnull) IDRPacketParser *packetParser;

/*!
 * @brief Register a listener
 * @param listener The listener
 */
- (void)addListener:(nonnull id <IDRDeviceListener>)listener;

/*!
 * @brief Unregister a listener
 * @param listener The listener
 */
- (void)removeListener:(nonnull id <IDRDeviceListener>)listener;

/*!
 * @brief Returns a copy of the array with current registered listeners
 * @return Array with listeners
 */
- (nonnull NSArray *)listeners;

/*!
 * @brief Connect the device
 *
 * This will result in a deviceConnected: message to all registered listeners
 */
- (void)connect;

/*!
 * @brief Disconnect the device
 *
 * This will result in a deviceDisconnected: message to all registered listeners
 */
- (void)disconnect;

/*!
 * @brief Send a packet to the device
 * @param packet The packet to send
 */
- (void)send:(nonnull IDRSendablePacket *)packet;

@end
