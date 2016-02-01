#pragma once

#include "../util/IDRCommon.h"

/*! 
 * @brief Regulation enumeration
 */
typedef NS_ENUM(uint8_t, IDRRegulation) {
    IDRRegulationNoneSelected = 255, ///< No regulation selected (RFID will not work)
    IDRRegulationETSI = 0, ///< ETSI/EN 302 208: 865.7 - 867.5 MHz, 2W ERP, 4 channels
    IDRRegulationFCC_IC = 1, ///< FCC 15.247: 902.0 - 928.0 MHz, 4W EIRP, FHSS
    IDRRegulationChina = 2, ///< 920.5 - 924.5 MHz, 4W EIRP, FHSS
    IDRRegulationAustralia = 3, ///< 921.375 - 924.375 MHz, 4W EIRP
    IDRRegulationJapan = 5, ///< ARIB STD-T107: 916.7 - 920.9 MHz, 4W EIRP
    IDRRegulationKorea = 6, ///< 917.0 - 920.8 MHz, 4W EIRP, FHSS
    IDRRegulationNewZealand = 7, ///< 922.875 - 924.375 MHz, 2W ERP
    IDRRegulationRussia = 8, ///< 866.0 - 867.6 MHz, 2W ERP
    IDRRegulationBrazil = 10, ///< 902 - 907.5 MHz and 915 - 928 MHz, 4W EIRP
    IDRRegulationVietnam = 12, ///< 866.3 MHz, 866.9 MHz, 867.5 Mhz, 2W ERP
    IDRRegulationTaiwan = 13, ///< NCC LP0002: 922.75 - 927.25MHz, 4W EIRP
    IDRRegulationIndonesia = 14, ///< 923.25 - 924.75 MHz, 2W ERP, FHSS
    IDRRegulationBangladesh = 15, ///< 922.875 MHz, 923.625 MHz, 2W ERP
    IDRRegulationMalaysia = 16, ///< 919.875 - 922.125 MHz, 2W ERP
    IDRRegulationVenezuela = 17, ///< 922.250 - 927.750 MHz, 4W EIRP, FHSS
    IDRRegulationPeru = 18, ///< 915.250 - 927.750 MHz, 4W EIRP, FHSS
    IDRRegulationBrunei = 19, ///< 923.250 - 924.750 MHz, 2W ERP, FHSS
};

/*! 
 * @brief Regulation enumeration
 */
@interface IDRRegulationWrapper : NSObject

/*!
 * @brief Initializes a wrapped object with a IDRRegulation enumeration value.
 * @param enumValue The IDRRegulation value.
 * @return IDRRegulation instance representing the enum value.
 */
-(nonnull instancetype) initWithValue:(IDRRegulation)enumValue;

/*!
 * @brief Retrieves a string representation of the wrapped IDRRegulation value.
 * @return String representation.
 */
-(nonnull NSString *) toString;

/*!
 * @brief The IDRRegulation value which is wrapped by this object.
 */
@property (nonatomic, readonly) IDRRegulation value;

/*!
 * @brief Creates a wrapped object with a IDRRegulation enumeration value.
 * @param value The IDRRegulation value.
 * @return IDRRegulation instance representing the enum value.
 */
+(nonnull instancetype) regulationWrapperWithValue:(IDRRegulation)value;

/*!
 * @brief Retrieves an array with all Regulations wrapped in IDRRegulationWrapper objects
 * @return NSArray with all Regulations wrapped in IDRRegulationWrapper objects
 */
+(nonnull NSArray<IDRRegulationWrapper *> *) allRegulations;

@end
