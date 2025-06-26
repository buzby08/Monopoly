//
// Created by busby08 on 16/06/25.
//

#include <array>
#include "Board.h"

#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Property.h"
#include "PropertyCSVReader.h"

std::vector<Property> Board::populate_properties() {
    std::vector<Property> all_properties = {};

    const std::vector<PropertyStruct> all_property_structs = PropertyCSVReader::read("properties.csv");

    for (auto & property_struct : all_property_structs) {
        Property temp_property(property_struct);
        all_properties.push_back(temp_property);
    }



    return all_properties;
}

bool Board::is_property(int space_number) const {
    for (auto & property_space_number : property_space_numbers) {
        if (space_number == property_space_number) return true;
    }

    return false;
}

Board::Board() {
    properties = populate_properties();

    for (auto & property : properties) {
        property_space_numbers.push_back(property.space());
    }
}


SpaceActions Board::get_space_action(int space_number) const {
    if (is_property(space_number)) return SpaceActions::Property;

    switch (space_number) {
        case 0:
            return SpaceActions::Go;

        case 4: return SpaceActions::IncomeTax;

        case 7:
        case 22:
        case 36:
            return SpaceActions::Chance;

        case 2:
        case 17:
        case 33:
            return SpaceActions::CommunityChest;

        case 10:
            return SpaceActions::Jail;

        case 20:
            return SpaceActions::FreeParking;

        case 38:
            return SpaceActions::LuxuryTax;

        case 30:
            return SpaceActions::GoToJail;

        default:
            return SpaceActions::Invalid;
    }
}

Property Board::get_space_property(int space_number) {
    for (auto & property : properties) {
        if (property.space() == space_number) return property;
    }

    throw std::invalid_argument("The provided space is not a valid property");
}

std::string Board::get_space_name(int space_number) {
    if (is_property(space_number)) return get_space_property(space_number).name();

    switch (get_space_action(space_number)) {
        case SpaceActions::Go: return "Go";
        case SpaceActions::IncomeTax: return "Income Tax";
        case SpaceActions::Chance: return "Chance";
        case SpaceActions::CommunityChest: return "Community Chest";
        case SpaceActions::Jail: return "Jail";
        case SpaceActions::FreeParking: return "Free Parking";
        case SpaceActions::LuxuryTax: return "Luxury Tax";
        case SpaceActions::GoToJail: return "Go To Jail";

        case SpaceActions::Invalid:
        default:
            return "N/A";
    }
}


