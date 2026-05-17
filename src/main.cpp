#include <fstream>

#include "AiPlayer.h"
#include "Ansi.h"
#include "BoardCreator.h"
#include "ChanceCards.h"
#include "UserPlayer.h"
#include "Game.h"
#include "Logger.h"
#include "utilities.h"


void AddPlayers() {
    std::cout << "Please enter the number of players (Minimum 2 players)" << std::endl;
    const int number_of_players = get_int(">> ", 2, LimitType::Min);

    for (int i = 0; i < number_of_players; i++) {
        clear_screen(true);

        int player_id = i + 1;

        const std::string player_color = Ansi::get_fg_from_user(
            std::format("Please enter the color that player {} will use.", player_id));

        std::cout << std::format("Is player {} a user-controlled player or a computer-controlled player?", player_id) << std::endl;
        std::cout << "1. User-controlled" << std::endl;
        std::cout << "2. Computer-controlled" << std::endl;
        const bool user_controlled = get_int(">> ", 1, 2) == 1;

        if (user_controlled) {
            UserPlayer temp_user_player(player_id, player_color);
            Game::players.push_back(std::make_unique<UserPlayer>(temp_user_player));
            continue;
        }

        std::cout << std::format("Should player {} (Computer controlled) have a short delay to allow you to view their moves?", player_id) << std::endl;
        std::cout << "1. Yes" << std::endl;
        std::cout << "2. No" << std::endl;

        const bool use_delay = get_int(">> ", 1, 2) == 1;

        AiPlayer temp_ai_player(player_id, player_color);

        if (use_delay)
            temp_ai_player.use_delay();

        Game::players.push_back(std::make_unique<AiPlayer>(temp_ai_player));
    }
}


int main() {
    // auto board_creator = BoardCreator();
    // std::cout << board_creator.GenerateBoard();

    Logger::log_file = "monopoly.LOG";

    std::cout << "Welcome to Monopoly, using c++" << std::endl;

    bool load_save = false;

    if (std::filesystem::is_regular_file("monopolySave.bin")) {
        std::cout << "A save file was found. Would you like to load it?" << std::endl;
        std::cout << "1. Yes" << std::endl;
        std::cout << "2. No" << std::endl;
        load_save = get_int(">> ", 1, 2) == 1;
    }

    if (load_save) {
        Game::load_state();
        Game::play();
    }


    Game::setupFromFile("settings.json");

    if (Game::players.empty()) {
        AddPlayers();
    }

    Game::play();

    return 0;
}
