#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief SGTIN EPC Filter value (GS1 EPC Tag Data Standard chapter 10.2)
 */
typedef NS_ENUM(uint8_t, IDRSgtinEpcFilterValue) {
    IDRSgtinEpcFilterValueOther = 0, ///< All Others
    IDRSgtinEpcFilterValuePosTradeItem = 1, ///< Point of sale (POS) trade item
    IDRSgtinEpcFilterValueFullCase = 2, ///< Full case for transport
    IDRSgtinEpcFilterValueReserved0x3 = 3, ///< Reserved
    IDRSgtinEpcFilterValueInnerPack = 4, ///< Inner pack trade item grouping for handling
    IDRSgtinEpcFilterValueReserved0x5 = 5, ///< Reserved
    IDRSgtinEpcFilterValueUnitLoad = 6, ///< Unit load
    IDRSgtinEpcFilterValueComponent = 7, ///< Unit inside trade item or component inside a product not intended for individual sale
};

/*! 
 * @brief SGTIN EPC Filter value (GS1 EPC Tag Data Standard chapter 10.2)
 */
@interface IDRSgtinEpcFilterValueWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRSgtinEpcFilterValue enumeration value.
 * @param enumValue The IDRSgtinEpcFilterValue value.
 * @return IDRSgtinEpcFilterValue instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRSgtinEpcFilterValue)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRSgtinEpcFilterValue value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRSgtinEpcFilterValue value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRSgtinEpcFilterValue value;

/*!
 * @brief Creates a wrapped object with a IDRSgtinEpcFilterValue enumeration value.
 * @param value The IDRSgtinEpcFilterValue value.
 * @return IDRSgtinEpcFilterValue instance representing the enum value.
 */
+(nonnull instancetype) sgtinEpcFilterValueWrapperWithValue:(IDRSgtinEpcFilterValue)value;

/*!
 * @brief Retrieves an array with all SgtinEpcFilterValues wrapped in IDRSgtinEpcFilterValueWrapper objects
 * @return NSArray with all SgtinEpcFilterValues wrapped in IDRSgtinEpcFilterValueWrapper objects
 */
+(nonnull NSArray<IDRSgtinEpcFilterValueWrapper *> *) allSgtinEpcFilterValues;

@end
