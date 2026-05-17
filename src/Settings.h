//
// Created by busby08 on 16/07/25.
//

#ifndef SETTINGS_H
#define SETTINGS_H
#include <string>
#include <nlohmann/json.hpp>

#include "Game.h"
#include "Player.h"

using json = nlohmann::json;


class Settings {
    std::string board_file_path = "board.csv";
    std::string properties_file_path = "properties.csv";
    int go_amount = 2000;
    int jail_exit_amount = 50;
    int roll_per_dice = 6;
    std::string players_file_path;

public:
    Settings() = default;
    explicit Settings(const std::string &settings_file_path);

    [[nodiscard]] std::string BoardFilePath() const { return board_file_path; }
    [[nodiscard]] std::string PropertiesFilePath() const { return properties_file_path; }
    [[nodiscard]] int GoAmount() const { return go_amount; }
    [[nodiscard]] int JailExitAmount() const { return jail_exit_amount; }
    [[nodiscard]] int RollPerDice() const { return roll_per_dice; }
    [[nodiscard]] std::string PlayersFilePath() const { return players_file_path; }

    [[nodiscard]] std::vector<std::unique_ptr<Player>> GetPlayers() const;
};



#endif //SETTINGS_H
