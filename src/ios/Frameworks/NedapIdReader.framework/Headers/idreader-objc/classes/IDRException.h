#pragma once

#include "../util/IDRCommon.h"

#include "../enums/IDREnums.h"

#include "IDRClassDeclarations.h"

/*! 
 * @brief Base class for exceptions from the API.
 */
@interface IDRException : NSException

/*!
 * @brief Initializes the IDRException.
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
