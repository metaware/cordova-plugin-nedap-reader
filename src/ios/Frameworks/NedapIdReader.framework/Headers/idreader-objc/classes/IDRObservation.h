#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"

#include "IDRClassDeclarations.h"

/*! 
 * @brief Represents an individual interrogation of one RFID tag.
 */
@interface IDRObservation : NSObject

/*! 
 * @brief Constructs a basic Observation
 * @param epc Byte array with the (binary) EPC
 */
- (nonnull instancetype)initWithEpc:(nonnull NSData *)epc;

/*! 
 * @brief Gets the binary EPC
 * @return Binary EPC as byte array
 */
- (nonnull NSData *)epc;

/*! 
 * @brief Gets the EPC represented as hexadecimal string
 * @return EPC as hexadecimal string
 */
- (nonnull NSString *)epcAsHexString;

/*! 
 * @brief Gets the received signal strength indicator (RSSI) of the observation.
 *
 * Note that common RSSI levels are negative, because the received power from a tag is (much) less than 0 dBm (= 1 mW).
 * 
 * @throws ObservationException if RSSI was not present in the metadata
 * 
 * @return RSSI in tenths of dBm
 */
- (int16_t)rssi;

/*! 
 * @brief Sets the RSSI
 * @param rssi RSSI in tenths of dBm
 */
- (void)setRssi:(int16_t) rssi;

/*! 
 * @brief Gets the frequency of the reader used during the observation.
 * 
 * @throws ObservationException if the frequency was not present in the metadata
 * 
 * @return Frequency in Hz
 */
- (uint32_t)frequency;

/*! 
 * @brief Sets the frequency
 * @param frequency Frequency in Hz
 */
- (void)setFrequency:(uint32_t) frequency;

/*! 
 * @brief Gets the phase difference between the transmitted and received signal during the observation.
 *
 * This phase number is between 0 and 63 and represents 180 degrees of phase data.
 * 
 * @throws ObservationException if phase was not present in the metadata
 * 
 * @return phase The phase difference
 */
- (uint8_t)phase;

/*! 
 * @brief Sets the phase
 * @param phase Phase between 0 and 63
 */
- (void)setPhase:(uint8_t) phase;

/*! 
 * @brief Gets the receive antenna of the reader used during the observation.
 * 
 * @throws ObservationException if the receive antenna was not present in the metadata
 * 
 * @return Antenna type
 */
- (IDRAntenna)receiveAntenna;

/*! 
 * @brief Sets the receive antenna
 * @param receiveAntenna Receive antenna
 */
- (void)setReceiveAntenna:(IDRAntenna) receiveAntenna;

/*! 
 * @brief Gets the transmit antenna of the reader used during the observation.
 * 
 * @throws ObservationException if the transmit antenna was not present in the metadata
 * 
 * @return Antenna type
 */
- (IDRAntenna)transmitAntenna;

/*! 
 * @brief Sets the transmit antenna
 * @param transmitAntenna Transmit antenna
 */
- (void)setTransmitAntenna:(IDRAntenna) transmitAntenna;

/*! 
 * @brief Gets the timestamp of the reader used during the observation.
 *
 * Timestamps should only be compared between observations within the current RFID action.
 * If e.g. the RFID reader is stopped or connection is lost, the timestamp might be reset.
 * 
 * @throws ObservationException if the timestamp was not present in the metadata
 * 
 * @return Timestamp in milliseconds
 */
- (uint32_t)timestamp;

/*! 
 * @brief Sets the timestamp
 * @param timestamp Timestamp in milliseconds
 */
- (void)setTimestamp:(uint32_t) timestamp;

/*! 
 * @brief Gets the beam ID of the reader used during the observation.
 * 
 * @throws ObservationException if the beam ID was not present in the metadata
 * 
 * @return Beam ID
 */
- (uint8_t)beamId;

/*! 
 * @brief Sets the beam ID
 * @param beamId The beam ID
 */
- (void)setBeamId:(uint8_t) beamId;

/*! 
 * @brief Gets the EPC CRC of the observation.
 * 
 * @throws ObservationException if the EPC CRC was not present in the metadata
 * 
 * @return CRC word
 */
- (uint16_t)epcCrc;

/*! 
 * @brief Sets the EPC CRC
 * @param epcCrc CRC word
 */
- (void)setEpcCrc:(uint16_t) epcCrc;

/*! 
 * @brief Gets the EPC PC of the observation.
 * 
 * @throws ObservationException if the EPC PC was not present in the metadata.
 * 
 * @return PC word
 */
- (uint16_t)epcPc;

/*! 
 * @brief Sets the EPC PC
 * @param epcPc PC word
 */
- (void)setEpcPc:(uint16_t) epcPc;

/*! 
 * @brief Gets the calculated motion of the tag. Only works when motion filtering is enabled.
 * 
 * @throws ObservationException if the motion was not present in the metadata.
 * 
 * @return Calculated tag motion
 */
- (uint32_t)motion;

/*! 
 * @brief Sets the motion
 * @param motion Motion
 */
- (void)setMotion:(uint32_t) motion;

/*! 
 * @brief Gets the tag (muted) status of the observation.
 * 
 * @throws ObservationException if the EPC PC was not present in the metadata.
 * 
 * @return Bitmask with tag status
 */
- (IDRTagStatusFlags)tagStatus;

/*! 
 * @brief Sets the tag status
 * @param tagStatus Tag status bitmask
 */
- (void)setTagStatus:(IDRTagStatusFlags) tagStatus;

/*! 
 * @brief Gets a string representation of this packet, suitable for logging purposes.
 * @return String representation of this packet.
 */
- (nonnull NSString *)toString;

/*! 
 * @brief Gets the binary EPC
 * @return Binary EPC as byte array
 */
@property(nonatomic, nonnull, readonly, getter=epc) NSData * epc;

/*! 
 * @brief Gets the EPC represented as hexadecimal string
 * @return EPC as hexadecimal string
 */
@property(nonatomic, nonnull, readonly, getter=epcAsHexString) NSString * epcAsHexString;

/*! 
 * @brief Gets the received signal strength indicator (RSSI) of the observation.
 *
 * Note that common RSSI levels are negative, because the received power from a tag is (much) less than 0 dBm (= 1 mW).
 * 
 * @throws ObservationException if RSSI was not present in the metadata
 * 
 * @return RSSI in tenths of dBm
 */
@property(nonatomic, readwrite, getter=rssi, setter=setRssi:) int16_t rssi;

/*! 
 * @brief Gets the frequency of the reader used during the observation.
 * 
 * @throws ObservationException if the frequency was not present in the metadata
 * 
 * @return Frequency in Hz
 */
@property(nonatomic, readwrite, getter=frequency, setter=setFrequency:) uint32_t frequency;

/*! 
 * @brief Gets the phase difference between the transmitted and received signal during the observation.
 *
 * This phase number is between 0 and 63 and represents 180 degrees of phase data.
 * 
 * @throws ObservationException if phase was not present in the metadata
 * 
 * @return phase The phase difference
 */
@property(nonatomic, readwrite, getter=phase, setter=setPhase:) uint8_t phase;

/*! 
 * @brief Gets the receive antenna of the reader used during the observation.
 * 
 * @throws ObservationException if the receive antenna was not present in the metadata
 * 
 * @return Antenna type
 */
@property(nonatomic, readwrite, getter=receiveAntenna, setter=setReceiveAntenna:) IDRAntenna receiveAntenna;

/*! 
 * @brief Gets the transmit antenna of the reader used during the observation.
 * 
 * @throws ObservationException if the transmit antenna was not present in the metadata
 * 
 * @return Antenna type
 */
@property(nonatomic, readwrite, getter=transmitAntenna, setter=setTransmitAntenna:) IDRAntenna transmitAntenna;

/*! 
 * @brief Gets the timestamp of the reader used during the observation.
 *
 * Timestamps should only be compared between observations within the current RFID action.
 * If e.g. the RFID reader is stopped or connection is lost, the timestamp might be reset.
 * 
 * @throws ObservationException if the timestamp was not present in the metadata
 * 
 * @return Timestamp in milliseconds
 */
@property(nonatomic, readwrite, getter=timestamp, setter=setTimestamp:) uint32_t timestamp;

/*! 
 * @brief Gets the beam ID of the reader used during the observation.
 * 
 * @throws ObservationException if the beam ID was not present in the metadata
 * 
 * @return Beam ID
 */
@property(nonatomic, readwrite, getter=beamId, setter=setBeamId:) uint8_t beamId;

/*! 
 * @brief Gets the EPC CRC of the observation.
 * 
 * @throws ObservationException if the EPC CRC was not present in the metadata
 * 
 * @return CRC word
 */
@property(nonatomic, readwrite, getter=epcCrc, setter=setEpcCrc:) uint16_t epcCrc;

/*! 
 * @brief Gets the EPC PC of the observation.
 * 
 * @throws ObservationException if the EPC PC was not present in the metadata.
 * 
 * @return PC word
 */
@property(nonatomic, readwrite, getter=epcPc, setter=setEpcPc:) uint16_t epcPc;

/*! 
 * @brief Gets the calculated motion of the tag. Only works when motion filtering is enabled.
 * 
 * @throws ObservationException if the motion was not present in the metadata.
 * 
 * @return Calculated tag motion
 */
@property(nonatomic, readwrite, getter=motion, setter=setMotion:) uint32_t motion;

/*! 
 * @brief Gets the tag (muted) status of the observation.
 * 
 * @throws ObservationException if the EPC PC was not present in the metadata.
 * 
 * @return Bitmask with tag status
 */
@property(nonatomic, readwrite, getter=tagStatus, setter=setTagStatus:) IDRTagStatusFlags tagStatus;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)observationWithObject:(nonnull const void *)object;

/*! 
 * @brief Constructs a basic Observation
 * @param epc Byte array with the (binary) EPC
 */
+ (nonnull instancetype)observationWithEpc:(nonnull NSData *)epc;


@end
