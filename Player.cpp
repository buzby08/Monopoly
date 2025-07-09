    //
// Created by busby08 on 15/06/25.
//

#include <string>
#include <nlohmann/json.hpp>
#include "Player.h"

#include <format>
#include <fstream>
#include <iostream>

#include "Board.h"
#include "Game.h"

#include <utility>

#include "Ansi.h"

using json = nlohmann::json;


Player::Player(const int id) : player_type(PlayerType::User), id(id), space(0), money(1500), get_out_of_jail_attempts(0),
                               get_out_of_jail_free(false){
    }

Player::Player(const std::string &save_file_path) : player_type(PlayerType::User) {
    std::ifstream f(save_file_path);
    json data;

    try {
        data = json::parse(f);
    } catch (json::parse_error &e) {
        std::cerr << "There was an error parsing the save file" << std::endl;
        exit(-1);
    }

    id = static_cast<int>(data["id"]);
    space = static_cast<int>(data["space"]);
    money = static_cast<int>(data["money"]);
    get_out_of_jail_attempts = static_cast<int>(data["get_out_of_jail_attempts"]);
    get_out_of_jail_free = static_cast<bool>(data["get_out_of_jail_free"]);
    color = "";
}

Player::Player(int id, std::string color) : player_type(PlayerType::User), id(id), space(0), money(1500), get_out_of_jail_attempts(0),
                               get_out_of_jail_free(false), color(std::move(color)){}


std::string Player::as_string() {
    return std::format(
        "Player {} is on space {} with ${}. They have had {} get out of jail attempts. Get out of jail card: {}",
        id, space, money, get_out_of_jail_attempts, get_out_of_jail_free);
}

void Player::add_money(const int amount) {
    money += amount;

    if (money < 0) money = 0;
}

void Player::remove_money(const int amount) {
    add_money(-1 * amount);
}

void Player::add_property(const Property &property) {
    properties.push_back(property);
}

void Player::remove_property(const Property& property) {
    for (int i = 0; i < properties.size(); i++) {
        if (properties[i] == property) {
            properties.erase(properties.begin() + i);
        }
    }
}

bool Player::has_property(const Property &property) {
    for (int i = 0; i < properties.size(); i++) {
        if (properties[i] == property) {
            return true;
        }
    }
    return false;
}

void Player::reset_get_out_of_jail_attempts() { get_out_of_jail_attempts = 0; }
void Player::increase_get_out_of_jail_attempts() { get_out_of_jail_attempts += 1; }



void Player::move_to_space(const int new_space) {
    space = new_space % Game::board.MaxBoardSpaces();
}

int Player::move_forward(int number_of_spaces) {
    const int old_space = space;
    int new_space = old_space;

    int attempts = 0;

    while (number_of_spaces > 0) {
        new_space = Game::board.get_next_space_number(new_space);
        number_of_spaces--;
        attempts++;

        if (new_space == Game::board.GoSpaceNumber()) {
            Game::passGo(this);
        }

        if (attempts > Game::max_roll) break;
    }

    space = new_space;

    return space;
}

int Player::move_backward(const int number_of_spaces) {
    const int old_space = space;
    int new_space = old_space - number_of_spaces;

    while (new_space < 0) {
        new_space = Game::board.MaxBoardSpaces() - new_space;
    }

    space = new_space;
    return space;
}

void Player::add_get_out_of_jail_free() {
    get_out_of_jail_free = true;
}

void Player::remove_get_out_of_jail_free() {
    get_out_of_jail_free = false;
}

int Player::calculate_score() const {
    int score = money;

    for (auto & property : properties) {
        score += property.rent();
    }

    return score;
}

int Player::Space() const { return space; }

std::string Player::current_state() {
    std::string message = color;

    if (in_jail)
        message += std::format("Player {} is in jail\n", id);

    if (!in_jail)
        message += std::format("Player {} is on space {} - {}\n", id, space, Game::board.get_space_name(space));

    message += std::format("They have ${}\n", money);

    if (properties.size() == 0) {
        message += "They have no properties\n";
        return message;
    }

    message += "Their properties are: \n";
    for (const auto& property : properties) {
        message += std::format("  - {} ({})\n", property.name(), propertyColorSet_to_string(property.color_set()));
    }
    return message;
}

void Player::enter_jail() {
    in_jail = true;
    space = Game::board.JailSpaceNumber();
}

void Player::exit_jail() { in_jail = false; }

bool Player::InJail() const { return in_jail; }

std::string Player::Color() const {
    return color;
}

int Player::GetOutOfJailAttempts() const { return get_out_of_jail_attempts; }
