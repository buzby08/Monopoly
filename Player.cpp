    //
// Created by busby08 on 15/06/25.
//

#include <string>
#include <nlohmann/json.hpp>
#include "Player.h"

#include <format>
#include <fstream>
#include <iostream>

    using json = nlohmann::json;

#include <stdexcept>

Player::Player(const int id) : player_type(PlayerType::User), id(id), space(0), money(0), get_out_of_jail_attempts(0),
                               get_out_of_jail_free(false) {
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
}

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


void Player::move_to_space(const int new_space) {
    space = new_space % 40;
}

int Player::move_forward(const int number_of_spaces) {
    space = (space + number_of_spaces) % 40;
    return space;
}



