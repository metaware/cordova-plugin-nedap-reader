//
//  CountryCodeToRegulationMapper.swift
//  IDHand2
//
//  Copyright © 2015 N.V. Nederlandsche Apparatenfabriek "NEDAP". All rights reserved.
//


import Foundation
import CoreLocation
import NedapIdReader


/// Maps country codes to supported !D Hand regulations
class CountryCodeToRegulationMapper {
    /// Returns country code when provided with a location
    func countryCodeForLocation(location: CLLocation, completionHandler:(countryCode: String?) -> ()) {
        let geoCoder = CLGeocoder()

        geoCoder.reverseGeocodeLocation(location) { (placemarks, error) -> Void in
            guard let placemarks = placemarks else {
                completionHandler(countryCode: nil)
                return
            }

            let currentPlacemark = placemarks.first
            completionHandler(countryCode: currentPlacemark?.ISOcountryCode)
        }
    }


    /// Returns regulation when provided with a country code
    func regulationForCountryCode(countryCode: String) -> IDRRegulation? {
        let regulationToCountryMap = countryToRegulationMap()
        return regulationToCountryMap[countryCode]
    }


    /// Returns countries for regulation
    func countriesForRegulation(regulation: IDRRegulationWrapper) -> [String] {
        let regulationToCountryMap = countryToRegulationMap()
        var returnArray = [String]()

        for (countryCode, regulationEnum) in regulationToCountryMap {
            if regulation.value == regulationEnum {
                if let countryName = NSLocale.currentLocale().displayNameForKey(NSLocaleCountryCode, value: countryCode) {
                    returnArray.append(countryName)
                } else {
                    returnArray.append(countryCode)
                }
            }
        }

        return returnArray
    }


    /// Returns all supported countries
    func allCountries() -> Dictionary<String, String> {
        var returnDictionary = [String: String]()

        let countryMap = countryToRegulationMap()
        for (countryCode, _) in countryMap {
            if let countryName = NSLocale.currentLocale().displayNameForKey(NSLocaleCountryCode, value: countryCode) {
                returnDictionary[countryCode] = countryName
            } else {
                returnDictionary[countryCode] = countryCode
            }
        }

        return returnDictionary
    }


    /// Retruns all regulations supported by the !D Hand API
    func allRegulations() -> [IDRRegulationWrapper] {
        return IDRRegulationWrapper.allRegulations().filter {
            $0.value != .NoneSelected
        }
    }

    
    /// Returns all regulation names
    func allRegulationNames() -> [String] {
        var regulationNamesArray = [String]()

        for regulation in self.allRegulations() {
            regulationNamesArray.append(regulation.toString())
        }

        return regulationNamesArray
    }


    /// Maps country to regulation map
    private func countryToRegulationMap() -> Dictionary<String, IDRRegulation> {
        var regulationToCountryMap = [String: IDRRegulation]()

        /**
        * Argentina
        */
        regulationToCountryMap["AR"] = IDRRegulation.FCC_IC
        /**
        * Armenia
        */
        regulationToCountryMap["AM"] = IDRRegulation.ETSI
        /**
        * Australia
        */
        regulationToCountryMap["AU"] = IDRRegulation.Australia
        /**
        * Austria
        */
        regulationToCountryMap["AT"] = IDRRegulation.ETSI
        /**
        * Azerbaijan
        */
        regulationToCountryMap["AZ"] = IDRRegulation.ETSI
        /**
        * Bangladesh
        */
        regulationToCountryMap["BD"] = IDRRegulation.Bangladesh
        /**
        * Belgium
        */
        regulationToCountryMap["BE"] = IDRRegulation.ETSI
        /**
        * Belarus
        */
        regulationToCountryMap["BY"] = IDRRegulation.ETSI
        /**
        * Bosnia and Herzegovina
        */
        regulationToCountryMap["BA"] = IDRRegulation.ETSI
        /**
        * Brazil
        */
        regulationToCountryMap["BR"] = IDRRegulation.Brazil
        /**
        * Brunei Darussalam
        */
        regulationToCountryMap["BN"] = IDRRegulation.Brunei
        /**
        * Bulgaria
        */
        regulationToCountryMap["BG"] = IDRRegulation.ETSI
        /**
        * Canada
        */
        regulationToCountryMap["CA"] = IDRRegulation.FCC_IC
        /**
        * China
        */
        regulationToCountryMap["CN"] = IDRRegulation.China
        /**
        * Colombia
        */
        regulationToCountryMap["CO"] = IDRRegulation.FCC_IC
        /**
        * Costa Rica
        */
        regulationToCountryMap["CR"] = IDRRegulation.FCC_IC
        /**
        * Croatia
        */
        regulationToCountryMap["HR"] = IDRRegulation.ETSI
        /**
        * Cyprus
        */
        regulationToCountryMap["CY"] = IDRRegulation.ETSI
        /**
        * Czech Republic
        */
        regulationToCountryMap["CZ"] = IDRRegulation.ETSI
        /**
        * Denmark
        */
        regulationToCountryMap["DK"] = IDRRegulation.ETSI
        /**
        * Dominican Republic
        */
        regulationToCountryMap["DO"] = IDRRegulation.FCC_IC
        /**
        * Estonia
        */
        regulationToCountryMap["EE"] = IDRRegulation.ETSI
        /**
        * Finland
        */
        regulationToCountryMap["FI"] = IDRRegulation.ETSI
        /**
        * France
        */
        regulationToCountryMap["FR"] = IDRRegulation.ETSI
        /**
        * Germany
        */
        regulationToCountryMap["DE"] = IDRRegulation.ETSI
        /**
        * Greece
        */
        regulationToCountryMap["GR"] = IDRRegulation.ETSI
        /**
        * Hong Kong
        * NOTE: Hong Kong also allows IDRRegulation.ETSI
        */
        regulationToCountryMap["HK"] = IDRRegulation.China
        /**
        * Hungary
        */
        regulationToCountryMap["HU"] = IDRRegulation.ETSI
        /**
        * Iceland
        */
        regulationToCountryMap["IS"] = IDRRegulation.ETSI
        /**
        * India
        */
        regulationToCountryMap["IN"] = IDRRegulation.ETSI
        /**
        * Indonesia
        */
        regulationToCountryMap["ID"] = IDRRegulation.Indonesia
        /**
        * Iran, Islamic Republic of
        */
        regulationToCountryMap["IR"] = IDRRegulation.ETSI
        /**
        * Ireland
        */
        regulationToCountryMap["IE"] = IDRRegulation.ETSI
        /**
        * Italy
        */
        regulationToCountryMap["IT"] = IDRRegulation.ETSI
        /**
        * Japan
        */
        regulationToCountryMap["JP"] = IDRRegulation.Japan
        /**
        * Jordan
        */
        regulationToCountryMap["JO"] = IDRRegulation.ETSI
        /**
        * Korea, Republic of
        */
        regulationToCountryMap["KR"] = IDRRegulation.Korea
        /**
        * Latvia
        */
        regulationToCountryMap["LV"] = IDRRegulation.ETSI
        /**
        * Lithuania
        */
        regulationToCountryMap["LT"] = IDRRegulation.ETSI
        /**
        * Luxembourg
        */
        regulationToCountryMap["LU"] = IDRRegulation.ETSI
        /**
        * Macedonia, The Former Yugoslav Republic of
        */
        regulationToCountryMap["MK"] = IDRRegulation.ETSI
        /**
        * Malaysia
        */
        regulationToCountryMap["MY"] = IDRRegulation.Malaysia
        /**
        * Malta
        */
        regulationToCountryMap["MT"] = IDRRegulation.ETSI
        /**
        * Mexico
        */
        regulationToCountryMap["MX"] = IDRRegulation.FCC_IC
        /**
        * Moldova, Republic of
        */
        regulationToCountryMap["MD"] = IDRRegulation.ETSI
        /**
        * Netherlands
        */
        regulationToCountryMap["NL"] = IDRRegulation.ETSI
        /**
        * Nigeria
        */
        regulationToCountryMap["NG"] = IDRRegulation.ETSI
        /**
        * New Zealand
        */
        regulationToCountryMap["NZ"] = IDRRegulation.NewZealand
        /**
        * Norway
        */
        regulationToCountryMap["NO"] = IDRRegulation.ETSI
        /**
        * Oman
        */
        regulationToCountryMap["OM"] = IDRRegulation.ETSI
        /**
        * Panama
        */
        regulationToCountryMap["PA"] = IDRRegulation.FCC_IC
        /**
        * Peru
        */
        regulationToCountryMap["PE"] = IDRRegulation.Peru
        /**
        * Poland
        */
        regulationToCountryMap["PL"] = IDRRegulation.ETSI
        /**
        * Portugal
        */
        regulationToCountryMap["PT"] = IDRRegulation.ETSI
        /**
        * Romania
        */
        regulationToCountryMap["RO"] = IDRRegulation.ETSI
        /**
        * Russian Federation
        */
        regulationToCountryMap["RU"] = IDRRegulation.Russia
        /**
        * Saudi Arabia
        */
        regulationToCountryMap["SA"] = IDRRegulation.ETSI
        /**
        * Serbia
        */
        regulationToCountryMap["RS"] = IDRRegulation.ETSI
        /**
        * Singapore
        */
        regulationToCountryMap["SG"] = IDRRegulation.China
        /**
        * Slovakia
        */
        regulationToCountryMap["SK"] = IDRRegulation.ETSI
        /**
        * Slovenia
        */
        regulationToCountryMap["SI"] = IDRRegulation.ETSI
        /**
        * South Africa
        */
        regulationToCountryMap["ZA"] = IDRRegulation.ETSI
        /**
        * Spain
        */
        regulationToCountryMap["ES"] = IDRRegulation.ETSI
        /**
        * Sweden
        */
        regulationToCountryMap["SE"] = IDRRegulation.ETSI
        /**
        * Switzerland
        */
        regulationToCountryMap["CH"] = IDRRegulation.ETSI
        /**
        * Taiwan
        */
        regulationToCountryMap["TW"] = IDRRegulation.Taiwan
        /**
        * Thailand
        */
        regulationToCountryMap["TH"] = IDRRegulation.China
        /**
        * Tunisia
        */
        regulationToCountryMap["TN"] = IDRRegulation.ETSI
        /**
        * Turkey
        */
        regulationToCountryMap["TR"] = IDRRegulation.ETSI
        /**
        * United Arab Emirates
        */
        regulationToCountryMap["AE"] = IDRRegulation.ETSI
        /**
        * United Kingdom
        */
        regulationToCountryMap["GB"] = IDRRegulation.ETSI
        /**
        * United States
        */
        regulationToCountryMap["US"] = IDRRegulation.FCC_IC
        /**
        * Uruguay
        */
        regulationToCountryMap["UY"] = IDRRegulation.FCC_IC
        /**
        * Venezuela
        */
        regulationToCountryMap["VE"] = IDRRegulation.Venezuela
        /**
        * Vietnam
        */
        regulationToCountryMap["VN"] = IDRRegulation.Vietnam

        // Countries for which RFID regulations exist,
        // but have not been implemented yet:
        // Montenegro
        // Chili

        return regulationToCountryMap
    }

}