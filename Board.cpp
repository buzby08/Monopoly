//
// Created by busby08 on 16/06/25.
//

#include <array>
#include "Board.h"

#include <format>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <nlohmann/json.hpp>

#include "utilities.h"
#include "Logger.h"
#include "Property.h"
#include "PropertyCSVReader.h"

std::vector<Property> Board::get_properties(const std::string &file_path) {
    std::vector<Property> all_properties = {};

    const std::vector<PropertyStruct> all_property_structs = PropertyCSVReader::read(file_path);

    for (auto & property_struct : all_property_structs) {
        Property temp_property(property_struct);
        if (get_space_action(temp_property.space()) == SpaceActions::Property) {
            all_properties.push_back(temp_property);
            continue;
        }

        Logger::warning(std::format("Property {} is not in the board, and is being ignored", temp_property.name()));
    }

    return all_properties;
}

std::vector<int> Board::get_property_space_numbers() const {
    std::vector<int> all_space_numbers = {};
    for (auto &property : properties) {
        all_space_numbers.push_back(property.space());
    }

    return all_space_numbers;
}

bool Board::is_property(int space_number) const {
    for (auto & property_space_number : property_space_numbers) {
        if (space_number == property_space_number) return true;
    }
    return false;
}

Board::Board(const std::string &board_file_path, const std::string &properties_file_path) {
    spaces = std::unordered_map<int, std::string>();
    properties = std::vector<Property>();

    if (board_file_path != "")
        spaces = read_spaces(board_file_path);

    if (properties_file_path != "")
        properties = get_properties(properties_file_path);

    property_space_numbers = get_property_space_numbers();
    max_board_spaces = spaces.size();
}


SpaceActions Board::get_space_action(int space_number) {
    return get_space_action(space_number, spaces);
}

Property Board::get_space_property(int space_number) {
    for (auto & property : properties) {
        if (property.space() == space_number) return property;
    }

    throw std::invalid_argument("The provided space is not a valid property");
}

std::string Board::get_space_name(const int space_number) {
    if (is_property(space_number)) return get_space_property(space_number).name();

    return space_action_to_string(get_space_action(space_number));
}

int Board::get_next_space_number(int current_space_number) const {
    while (true) {
        current_space_number = (current_space_number + 1) % max_board_spaces;

        if (spaces.contains(current_space_number)) return current_space_number;
    }
}

std::unordered_map<int, std::string> Board::read_spaces(const std::string& file_path) {
    std::unordered_map<int, std::string> result;

    std::ifstream file(file_path);

    std::string header_line;
    getline(file, header_line);

    if (header_line != "spaceNumber,type")
        Logger::error(std::format(
            "The format in {} is invalid. Please correct this according to README.md",
            file_path));

    std::string line;

    while (getline(file, line)) {
        std::vector<std::string> items = split_string(line, ',');
        if (items.size() < 2) {
            Logger::warning(std::format(
                "An invalid entry in {} has been found: `{}`",
                file_path, line));
            continue;
        }

        int board_space = stoi(items[0]);
        const std::string& space_name = items[1];
        result[board_space] = space_name;

        if (get_space_action(board_space, result) == SpaceActions::Jail)
            jail_space_number = board_space;

        if (get_space_action(board_space, result) == SpaceActions::Go)
            go_space_number = board_space;

    }

    return result;
}

SpaceActions Board::get_space_action(int space_number, const std::unordered_map<int, std::string> &spaces) {
    if (space_actions.contains(space_number)) {
        return space_actions.at(space_number);
    }

    if (!spaces.contains(space_number)) return SpaceActions::Invalid;

    const std::string space_action = spaces.at(space_number);

    SpaceActions actual_space_action = string_to_space_action(space_action);

    space_actions[space_number] = actual_space_action;
    return actual_space_action;
}


