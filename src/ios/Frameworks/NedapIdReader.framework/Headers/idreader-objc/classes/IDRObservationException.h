#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"
#include "../classes/IDRException.h"
#include "IDRClassDeclarations.h"

/*! 
 * @brief An ObservationException is thrown when the user tries to retrieve a field from an Observation, which was not included in the metadata.
 */
@interface IDRObservationException : IDRException

/*!
 * @brief Initializes the IDRObservationException.
 *
 * @param name The name of the exception
 * @param reason A human-readable message string summarizing the reason for the exception
 * @param userInfo A dictionary containing user-defined information relating to the exception
 */
- (nonnull instancetype)initWithName:(nonnull NSString *)name reason:(nullable NSString *)reason userInfo:(nullable NSDictionary *)userInfo;

/*!
 * @brief Constructs a wrapped class from a C++ object.
 *
 * Creates an internally managed copy of the C++ object. For internal API usage only.
 * 
 * @param object Pointer to the C++ object.
 */
+ (nonnull instancetype)exceptionWithObject:(nonnull const void *)object;


@end
