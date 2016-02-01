#import "util/IDRCommon.h"

#import "classes/IDRClasses.h"

@class IDRDevice;

/*!
 * @brief Protocol for receiving callbacks from the API
 *
 * Classes that wish to receive callbacks from this API must conform to this protocol and register themselves
 * to the IDRDevice. Upon receiving packets from the device, the API first checks whether the listener implements
 * a packet-specific callback. If yes, that callback is called, otherwise the fallback device:receivedPacket: is called.
 */
@protocol IDRDeviceListener <NSObject>
@optional

/*!
 * @brief Callback for when the device is connected.
 * @param device The device which is connected.
 */
- (void)deviceConnected:(nonnull IDRDevice *)device;

/*!
 * @brief Callback for when the device is disconnected.
 * @param device The device which is disconnected.
 */
- (void)deviceDisconnected:(nonnull IDRDevice *)device;

/*!
 * @brief Callback for when packet parsing failed within the API.
 * @param device The associated device.
 * @param error The error that occurred.
 */
- (void)device:(nonnull IDRDevice *)device parsingFailedWithError:(nonnull NSError *)error;

/*! 
 * @brief The BarcodeReaderData packet contains the barcode symbology and barcode data for a successful barcode read.
 *
 * @param device The device from which the packet was received.
 * @param packet The received BarcodeReaderDataPacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedBarcodeReaderDataPacket:(nonnull IDRBarcodeReaderDataPacket *) packet;

/*! 
 * @brief The BarcodeReaderStarted packet is received when the barcode reader has started reading.
 *
 * @param device The device from which the packet was received.
 * @param packet The received BarcodeReaderStartedPacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedBarcodeReaderStartedPacket:(nonnull IDRBarcodeReaderStartedPacket *) packet;

/*! 
 * @brief The BarcodeReaderStopped packet is received when the barcode reader has stopped reading.
 *
 * @param device The device from which the packet was received.
 * @param packet The received BarcodeReaderStoppedPacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedBarcodeReaderStoppedPacket:(nonnull IDRBarcodeReaderStoppedPacket *) packet;

/*! 
 * @brief A ButtonEvent is received when the user presses or releases the button.
 *
 * @param device The device from which the packet was received.
 * @param packet The received ButtonEventPacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedButtonEventPacket:(nonnull IDRButtonEventPacket *) packet;

/*! 
 * @brief The Bye packet is received as a response to the Hello command.
 *
 * @param device The device from which the packet was received.
 * @param packet The received ByePacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedByePacket:(nonnull IDRByePacket *) packet;

/*! 
 * @brief The EpcGen2Session packet contains the current configured EPC Gen2 session parameters.
 *
 * @param device The device from which the packet was received.
 * @param packet The received EpcGen2SessionPacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedEpcGen2SessionPacket:(nonnull IDREpcGen2SessionPacket *) packet;

/*! 
 * @brief An Error packet is received when something has gone wrong in the reader.
 *
 * An error contains a category and a code within the category. Use isProtocolError, isStateError, etc to check for the error type.
 *
 * @param device The device from which the packet was received.
 * @param packet The received ErrorPacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedErrorPacket:(nonnull IDRErrorPacket *) packet;

/*! 
 * @brief An InventoryCompleted packet is received when the EPC Gen2 Inventory has completed
 *
 * The inventory can be completed by either stopping an inventory, or when the StartInventoryOnce has completed autonomously.
 *
 * @param device The device from which the packet was received.
 * @param packet The received InventoryCompletedPacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedInventoryCompletedPacket:(nonnull IDRInventoryCompletedPacket *) packet;

/*! 
 * @brief An InventoryObservation is received when one or more RFID tags have been queried successfully. It contains the EPC(s) and additional metadata.
 *
 * @param device The device from which the packet was received.
 * @param packet The received InventoryObservationPacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedInventoryObservationPacket:(nonnull IDRInventoryObservationPacket *) packet;

/*! 
 * @brief The OutputPower packet contains the current configured RFID output power and the output power boundaries of the reader.
 *
 * @param device The device from which the packet was received.
 * @param packet The received OutputPowerPacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedOutputPowerPacket:(nonnull IDROutputPowerPacket *) packet;

/*! 
 * @brief The PowerState packet is received as a response to the GetPowerState command and contains the current battery level, battery health and power source.
 *
 * @param device The device from which the packet was received.
 * @param packet The received PowerStatePacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedPowerStatePacket:(nonnull IDRPowerStatePacket *) packet;

/*! 
 * @brief The ProgramEpcResult packet is received when the ProgramEpc command is finished.
 *
 * @param device The device from which the packet was received.
 * @param packet The received ProgramEpcResultPacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedProgramEpcResultPacket:(nonnull IDRProgramEpcResultPacket *) packet;

/*! 
 * @brief The Regulation packet contains the current configured regulation and the regulations supported by the reader.
 *
 * @param device The device from which the packet was received.
 * @param packet The received RegulationPacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedRegulationPacket:(nonnull IDRRegulationPacket *) packet;

/*! 
 * @brief The ResetCompleted packet is received as a response to the Reset command.
 *
 * When the reset is complete, any RFID action is stopped and all non-persistent settings are set to default.
 *
 * @param device The device from which the packet was received.
 * @param packet The received ResetCompletedPacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedResetCompletedPacket:(nonnull IDRResetCompletedPacket *) packet;

/*! 
 * @brief The SerialNumber packet is received as a response to the GetSerialNumber command.
 *
 * @param device The device from which the packet was received.
 * @param packet The received SerialNumberPacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedSerialNumberPacket:(nonnull IDRSerialNumberPacket *) packet;

/*! 
 * @brief The StoreFirmwareBlockCompleted packet is received as a response to the StoreFirmwareBlock command.
 *
 * It acknowledges that the firmware data block is received correctly and stored into flash.
 *
 * @param device The device from which the packet was received.
 * @param packet The received StoreFirmwareBlockCompletedPacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedStoreFirmwareBlockCompletedPacket:(nonnull IDRStoreFirmwareBlockCompletedPacket *) packet;

/*! 
 * @brief The UserLedMode packet contains the current state of the user LED.
 *
 * @param device The device from which the packet was received.
 * @param packet The received UserLedModePacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedUserLedModePacket:(nonnull IDRUserLedModePacket *) packet;

/*! 
 * @brief The Version packet is received as a response to the GetVersion command.
 *
 * @param device The device from which the packet was received.
 * @param packet The received VersionPacket packet.
 */
- (void)device:(nonnull IDRDevice *)device receivedVersionPacket:(nonnull IDRVersionPacket *) packet;

/*!
 * @brief Fallback for when the class does not respond to the specific selector.
 *
 * @param device The device from which the packet was received.
 * @param packet The received packet not handled by the specific selector.
 */
- (void)device:(nonnull IDRDevice *)device receivedPacket:(nonnull IDRPacket *)packet;

@end

/*!
 * @brief Helper class for handling received packets.
 */
@interface IDRDeviceListenerSelector : NSObject {

}

/*!
 * @brief Sends the correct selector to the listener for the provided receivable packet.
 *
 * If the listener does not respond to the selector, the fallback method device:receivedPacket: is used.
 *
 * @param listener The listener to perform the selector on
 * @param sender The device from which the packet was received
 * @param packet The received packet
 */
+ (void)performOptionalSelectorOn:(nonnull id<IDRDeviceListener>)listener sender:(nonnull IDRDevice *)sender packet:(nonnull IDRPacket *)packet;

@end
