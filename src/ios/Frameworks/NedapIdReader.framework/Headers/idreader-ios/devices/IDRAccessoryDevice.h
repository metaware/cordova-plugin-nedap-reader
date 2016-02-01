#pragma once

#import <Foundation/Foundation.h>
#import "../../idreader-objc/IDRIdReaderObjc.h"
#import <ExternalAccessory/ExternalAccessory.h>

/*!
 * @brief Represents a connection with an !D Hand over an External Accessory Protocol Session.
 *
 * The device needs to be initialized with a valid EAAccessory object, which supports the com.nedap.retail.idreader external
 * accessory protocol. After connecting (opening the EASession), packets can be sent using the send: message. To receive
 * callbacks for received packets, register one or more listeners that implement IDRDeviceListener protocol.
 */
@interface IDRAccessoryDevice : IDRDevice <EAAccessoryDelegate, NSStreamDelegate>

/*!
 * @brief Constructs an IDRAccessoryDevice with an associated external accessory.
 *
 * The accessory must support the com.nedap.retail.idreader external accessory protocol.
 *
 * @param accessory The associated external accessory
 */
+ (nonnull instancetype)deviceWithAccessory:(nonnull EAAccessory *)accessory;

/*!
 * @brief Constructs an IDRAccessoryDevice with an associated external accessory and device listener.
 *
 * The accessory must support the com.nedap.retail.idreader external accessory protocol.
 *
 * @param accessory The associated external accessory
 * @param listener The listener to be added
 */
+ (nonnull instancetype)deviceWithAccessory:(nonnull EAAccessory *)accessory listener:(nonnull id <IDRDeviceListener>)listener;

/*!
 * @brief Constructs an IDRAccessoryDevice with an associated external accessory.
 *
 * The accessory must support the com.nedap.retail.idreader external accessory protocol.
 *
 * @param accessory The associated external accessory
 * @return self
 */
- (nonnull instancetype)initWithAccessory:(nonnull EAAccessory *)accessory;

/*!
 * @brief Opens the external accessory protocol session.
 */
- (void)connect;

/*!
 * @brief Closes the external accessory protocol session.
 */
- (void)disconnect;

/*!
 * @brief Retrieves the associated external accessory.
 * @return The associated external accessory
 */
- (nonnull EAAccessory *)accessory;

@end
