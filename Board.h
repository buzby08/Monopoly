//
// Created by busby08 on 16/06/25.
//

#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <nlohmann/json.hpp>

#include "Property.h"

using json = nlohmann::json;

enum class SpaceActions {
    Go,
    Property,
    IncomeTax,
    CommunityChest,
    Chance,
    Station,
    FreeParking,
    Jail,
    SuperTax,
    GoToJail,
    Utility,
    Invalid
};

inline std::string space_action_to_string(const SpaceActions e) {
    switch (e) {
        case SpaceActions::Go: return "Go";
        case SpaceActions::Property: return "Property";
        case SpaceActions::IncomeTax: return "Income Tax";
        case SpaceActions::CommunityChest: return "Community Chest";
        case SpaceActions::Chance: return "Chance";
        case SpaceActions::Station: return "Station";
        case SpaceActions::FreeParking: return "Free Parking";
        case SpaceActions::Jail: return "Jail";
        case SpaceActions::SuperTax: return "Super Tax";
        case SpaceActions::GoToJail: return "Go To Jail";
        case SpaceActions::Utility: return "Utility";
        case SpaceActions::Invalid: return "Invalid";
        default: return "unknown";
    }
}

inline SpaceActions string_to_space_action(const std::string& space) {
    std::unordered_map<std::string, SpaceActions> space_actions_map = {
        {"Go", SpaceActions::Go},
        {"Property", SpaceActions::Property},
        {"IncomeTax", SpaceActions::IncomeTax},
        {"CommunityChest", SpaceActions::CommunityChest},
        {"Chance", SpaceActions::Chance},
        {"Station", SpaceActions::Station},
        {"FreeParking", SpaceActions::FreeParking},
        {"Jail", SpaceActions::Jail},
        {"SuperTax", SpaceActions::SuperTax},
        {"GoToJail", SpaceActions::GoToJail},
        {"Utility", SpaceActions::Utility}
    };

    bool is_in = space_actions_map.contains(space);

    if (!is_in) return SpaceActions::Invalid;

    return space_actions_map[space];
}

class Board {
    std::unordered_map<int, SpaceActions> space_actions;
    std::unordered_map<int, std::string> spaces;
    std::vector<Property> properties;
    std::vector<int> property_space_numbers;
    int jail_space_number;
    int max_board_spaces;
    int go_space_number;

    std::vector<Property> get_properties(const std::string &file_path);
    std::vector<int> get_property_space_numbers() const;
    bool is_property(int space_number) const;

    std::unordered_map<int, std::string> read_spaces(const std::string& file_path);

    SpaceActions get_space_action(int space_number, const std::unordered_map<int, std::string> &spaces);


public:
    explicit Board(const std::string &board_file_path, const std::string &properties_file_path);


    /**
     * Returns the action that the inputted space requires (such as Go, Community Chest, Go To Jail etc)
     * @param space_number The space number (from 0 to 39, inclusive)
     * @return The space action from the `SpaceActions` enum. This is `SpaceActions::Invalid` if not a valid space number
     */
    SpaceActions get_space_action(int space_number);
    Property get_space_property(int space_number);
    std::string get_space_name(int space_number);

    int get_next_space_number(int current_space_number) const;

    int JailSpaceNumber() const { return jail_space_number; }
    int MaxBoardSpaces() const { return max_board_spaces; }
    int GoSpaceNumber() const { return go_space_number; }
};



#endif //BOARD_H
