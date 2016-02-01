/*
 * Common header files, types and includes.
 */

#pragma once

// Include foundation.
#import <Foundation/Foundation.h>

// Define NS_ENUM and NS_OPTIONS in GNUstep.
#ifdef GNUSTEP
#    define NS_ENUM(_type, _name) enum _name : _type _name; enum _name : _type
#    define NS_OPTIONS(_type, _name) _type _name; enum : _type
#endif

// Common types.
typedef unsigned char byte;
