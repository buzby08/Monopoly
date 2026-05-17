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

#include "Ansi.h"
#include "utilities.h"
#include "Logger.h"
#include "Property.h"
#include "PropertyCSVReader.h"

std::vector<int> Board::get_property_space_numbers() const
{
    std::vector<int> all_space_numbers = {};
    for (auto& property : properties) {
        all_space_numbers.push_back(property->space());
    }

    return all_space_numbers;
}

bool Board::is_property(const int space_number) const
{
    return std::ranges::any_of(
        property_space_numbers,
        [&](const int property_space_number) { return property_space_number == space_number; });
}

int Board::get_property_index(const int space_number) const
{
    for (int i = 0; i < property_space_numbers.size(); i++) {
        if (space_number == property_space_numbers[i]) return i;
    }

    throw std::invalid_argument("Property index out of range");
}

std::unordered_map<int, std::string> Board::read_spaces(const std::string& file_path)
{
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

        if (get_space_action(board_space) == SpaceActions::Jail)
            jail_space_number = board_space;

        if (get_space_action(board_space) == SpaceActions::Go)
            go_space_number = board_space;
    }

    return result;
}

SpaceActions Board::get_space_action(const int space_number)
{
    if (space_actions.contains(space_number)) {
        return space_actions.at(space_number);
    }

    if (!spaces.contains(space_number)) return SpaceActions::Invalid;

    const std::string& space_action = spaces.at(space_number);

    const SpaceActions actual_space_action = string_to_space_action(space_action);

    space_actions[space_number] = actual_space_action;
    return actual_space_action;
}

void Board::initialise(const std::string& new_board_file_path, const std::string& new_properties_file_path)
{
    spaces = std::unordered_map<int, std::string>();
    properties = std::vector<std::unique_ptr<Property>>();
    Board::board_file_path = new_board_file_path;
    Board::properties_file_path = new_properties_file_path;

    if (!new_board_file_path.empty())
        spaces = read_spaces(new_board_file_path);

    if (!new_properties_file_path.empty())
        properties = get_properties(new_properties_file_path);

    property_space_numbers = get_property_space_numbers();
    max_board_spaces = static_cast<int>(spaces.size());
}

std::vector<std::unique_ptr<Property>> Board::get_properties(const std::string& file_path)
{
    std::vector<std::unique_ptr<Property>> all_properties = {};

    const std::vector<PropertyStruct> all_property_structs = PropertyCSVReader::read(file_path);

    for (auto& property_struct : all_property_structs) {
        Property temp_property(property_struct);
        if (get_space_action(temp_property.space()) == SpaceActions::Property) {
            all_properties.push_back(std::make_unique<Property>(temp_property));
            continue;
        }

        Logger::warning(std::format("Property {} is not in the board, and is being ignored", temp_property.name()));
    }

    return all_properties;
}

Board::Board(const std::string& board_file_path, const std::string& properties_file_path)
{
    initialise(board_file_path, properties_file_path);
}

Board::Board() : jail_space_number(0), max_board_spaces(0), go_space_number(0)
{
    initialise(board_file_path, properties_file_path);
}

void Board::loadBoard()
{
    spaces = std::unordered_map<int, std::string>();
    space_actions = std::unordered_map<int, SpaceActions>();

    if (!board_file_path.empty())
        spaces = read_spaces(board_file_path);

    property_space_numbers = get_property_space_numbers();
    max_board_spaces = static_cast<int>(spaces.size());

    for (const std::unique_ptr<Property>& unique_property : properties)
    {
        Property* property = unique_property.get();
        if (property->owner_id() != -1)
        {
            Player* owner = Game::get_player_with_id(property->owner_id());
            
            if (owner != nullptr)
                property->set_owner(owner);
        }
    }
}

vector<Property*> Board::get_properties_by_player(const int player_id) const
{
    std::vector<Property*> owned_properties;

    for (int i = 0; i < properties.size(); i++) {
        Property* property = properties[i].get();
        if (property->owner_id() == player_id) owned_properties.push_back(property);
    }

    return owned_properties;
}

Property* Board::get_space_property(const int space_number) const
{
    for (auto& property : properties) {
        if (property->space() == space_number) return property.get();
    }

    throw std::invalid_argument("The provided space is not a valid property");
}

std::string Board::get_space_string(const int space_number)
{
    try {
        return get_space_property(space_number)->get_name_and_color_string();
    }
    catch (std::invalid_argument& _) {
        return Ansi::reset + get_space_name(space_number);
    }
}

std::string Board::get_space_name(const int space_number)
{
    if (is_property(space_number)) return get_space_property(space_number)->name();

    return space_action_to_string(get_space_action(space_number));
}

int Board::get_next_space_number(int current_space_number) const
{
    Logger::info(std::format("Beginning Board::get_next_space_number: Current space number: {}", current_space_number));
    while (true) {
        current_space_number = (current_space_number + 1) % max_board_spaces;
        Logger::info(std::format("New current_space_number: {}", current_space_number));
        Logger::info(std::format("Space number in spaces: {}", spaces.contains(current_space_number)));
        if (spaces.contains(current_space_number)) return current_space_number;
    }
}

void Board::mark_owned(const int space_number, Player* new_owner) const
{
    if (!is_property(space_number)) throw std::invalid_argument("The provided space is not a valid property");

    const int property_index = get_property_index(space_number);
    properties[property_index]->set_owner(new_owner);
}

bool Board::is_owned(const int space_number) const
{
    if (!is_property(space_number)) throw std::invalid_argument("The provided space is not a valid property");

    const int property_index = get_property_index(space_number);

    return properties[property_index]->owned();
}

std::vector<Property*> Board::get_properties_by_owner(const int owner_id) const
{
    std::vector<Property*> owned_properties;
    for (auto& property : properties) {
        if (property->owner_id() == owner_id) owned_properties.push_back(property.get());
    }

    return owned_properties;
}
