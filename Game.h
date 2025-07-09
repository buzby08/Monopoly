//
// Created by busby08 on 16/06/25.
//

#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include <random>

#include "Board.h"
#include "Player.h"


class Game {
    inline static int turn = 0;

    static void nextTurn();
    static void doSpaceAction(SpaceActions action);
    static Player * current_player();

    static void landOnGo();
    static void goToJail();
    static void onJailSpace();
    static void onProperty();
    static void payRent(Player *receiving_player, const Property &property);
    static void get_out_of_jail();
    static void declare_bankruptcy();

    static void buyProperty(Player *player, const Property &property);

public:
    inline static auto board = Board("", "");

    static constexpr int go_amount = 200;
    static constexpr int jail_exit_amount = 50;
    static constexpr int max_roll = 12;



    static void setupBoard(const std::string &board_file_path, const std::string &properties_file_path) {
        board = Board(board_file_path, properties_file_path);
    }

    /**
     * A vector of all the players in the game. This must be a subclass of the Player class (which is not instantiable),
     * such as UserPlayer or AiPlayer
     */
    inline static std::vector<std::unique_ptr<Player>> players = {};
    /**
     * Starts the game loop
     */
    [[noreturn]] static void play();
    /**
     * Rolls a standard 6 sided dice and returns the result.
     * @return The dice roll, from 1 to 6 (inclusive)
     */
    static int rollDice();

    static void passGo(Player *player);
    [[noreturn]] static void endGame(bool ignore_player = false, int player_to_ignore = 0);
};



#endif //GAME_H
