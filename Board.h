//
// Created by busby08 on 16/06/25.
//

#ifndef BOARD_H
#define BOARD_H

#include <array>

#include "Property.h"

enum class SpaceActions {
    Go,
    Property,
    IncomeTax,
    CommunityChest,
    Chance,
    Station,
    FreeParking,
    Jail,
    LuxuryTax,
    GoToJail,
    Invalid
};

inline std::string to_string(const SpaceActions e) {
    switch (e) {
        case SpaceActions::Go: return "Go";
        case SpaceActions::Property: return "Property";
        case SpaceActions::IncomeTax: return "Income Tax";
        case SpaceActions::CommunityChest: return "Community Chest";
        case SpaceActions::Chance: return "Chance";
        case SpaceActions::Station: return "Station";
        case SpaceActions::FreeParking: return "Free Parking";
        case SpaceActions::Jail: return "Jail";
        case SpaceActions::LuxuryTax: return "Luxury Tax";
        case SpaceActions::GoToJail: return "Go ToJ ail";
        case SpaceActions::Invalid: return "Invalid";
        default: return "unknown";
    }
}

class Board {
private:
    std::vector<Property> properties;
    std::vector<int> property_space_numbers;
    static std::vector<Property> populate_properties();

    bool is_property(int space_number) const;

public:
    Board();

    static constexpr int jail_space = 10;

    /**
     * Returns the action that the inputted space requires (such as Go, Community Chest, Go To Jail etc)
     * @param space_number The space number (from 0 to 39, inclusive)
     * @return The space action from the `SpaceActions` enum. This is `SpaceActions::Invalid` if not a valid space number
     */
    SpaceActions get_space_action(int space_number) const;
    Property get_space_property(int space_number);
    std::string get_space_name(int space_number);
};



#endif //BOARD_H
