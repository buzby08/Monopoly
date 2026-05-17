//
// Created by busby08 on 16/07/25.
//

#include "Settings.h"

#include <fstream>

#include "Ansi.h"

Settings::Settings(const std::string &settings_file_path) {
    std::ifstream file(settings_file_path);
    json data = json::parse(file);

    board_file_path = data.value("boardFilePath", board_file_path);
    properties_file_path = data.value("propertiesFilePath", properties_file_path);
    go_amount = data.value("goAmount", go_amount);
    jail_exit_amount = data.value("jailExitAmount", jail_exit_amount);
    roll_per_dice = data.value("rollPerDice", roll_per_dice);
    players_file_path = data.value("playersFilePath", players_file_path);

}

std::vector<std::unique_ptr<Player>> Settings::GetPlayers() const {
    std::vector<std::unique_ptr<Player>> players = {};

    if (players_file_path.empty())
        return players;

    std::ifstream file(players_file_path);
    json data = json::parse(file);

    if (!data.is_array())
        throw std::runtime_error("Invalid players file - JSON data must be an array");

    for (const auto& raw_player_data : data.items()) {
        const auto& player_data = raw_player_data.value();
        int id = player_data.value("id", -1);
        bool computer_controlled = player_data.value("computer-controlled", false);
        bool use_delay = player_data.value("use-delay", false);
        std::string raw_color = player_data.value("color", std::string());
        std::string color = Ansi::string_to_fg_color(raw_color);

        if (computer_controlled && use_delay) {
            auto temp_player = AiPlayer(id, color);
            temp_player.use_delay();
            players.push_back(std::make_unique<AiPlayer>(temp_player));
            continue;
        }

        if (computer_controlled) {
            auto temp_player = AiPlayer(id, color);
            players.push_back(std::make_unique<AiPlayer>(temp_player));
            continue;
        }

        auto temp_player = UserPlayer(id, color);
        players.push_back(std::make_unique<UserPlayer>(temp_player));
    }

    return players;
}
