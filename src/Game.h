//
// Created by busby08 on 16/06/25.
//

#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include <random>
#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <atomic>
#include <thread>


#include "Board.h"
#include "Player.h"
#include "AiPlayer.h"
#include "UserPlayer.h"


CEREAL_REGISTER_TYPE(AiPlayer);

CEREAL_REGISTER_TYPE(UserPlayer);

CEREAL_REGISTER_POLYMORPHIC_RELATION(Player, UserPlayer);

CEREAL_REGISTER_POLYMORPHIC_RELATION(Player, AiPlayer);


class Game {
    static std::atomic<bool> running;

    inline static int turn = 0;

    static void nextTurn();

    static int getPreviousPlayerTurnNumber();

    static int getNextPlayerTurnNumber();

    static void doSpaceAction(SpaceActions action);

    static Player *currentPlayer();

    static void landOnGo();

    static void goToJail();

    static void onJailSpace();

    static void onProperty();

    static void payRent(Player* receiving_player, const Property* property);

    static void getOutOfJail();

    static void declare_bankruptcy();

    static void buyProperty(Player *player, const Property* property);

    static void chanceCard();

    static char gameState(const std::string &additional_message = "", bool force_from_user = false);

    static void doBankruptCheck();
    
    static void transfer_ownership(const Property* property, Player* player);

public:
    inline static Board board = Board("", "");
    inline static std::atomic<bool> paused = false;

    inline static int go_amount = 200;
    inline static int jail_exit_amount = 50;
    inline static int max_roll = 12;
    inline static int roll_per_dice = 6;


    static void setupBoard(const std::string &board_file_path, const std::string &properties_file_path) {
        board = Board(board_file_path, properties_file_path);
    }

    static void setupFromFile(const std::string &settings_file_path);

    /**
     * A vector of all the players in the game. This must be a subclass of the Player class (which is not instantiable),
     * such as UserPlayer or AiPlayer
     */
    inline static std::vector<std::unique_ptr<Player>> players = {};
    /**
     * Starts the game loop
     */
    [[noreturn]] static void play();
    
    static Player* get_player_with_id(int id);

    /**
     * Rolls a standard 6 sided dice and returns the result.
     * @return The dice roll, from 1 to 6 (inclusive)
     */
    static int rollDice();

    static void save_state(const std::string &save_file = "monopolySave.bin");

    static void load_state(const std::string &save_file = "monopolySave.bin");

    static void passGo(Player *player);

    static void pauseMenu();

    [[noreturn]] static void endGame();
};


#endif //GAME_H
