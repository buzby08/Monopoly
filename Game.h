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
    int turn = 0;
    Board board;

    std::uniform_int_distribution<> random;
    std::mt19937 mersenne_twister_engine;

    void nextTurn();
    void doSpaceAction(SpaceActions action);
    Player * current_player() const;

    void landOnGo() const;
    void goToJail() const;
    void onJailSpace() const;
    void onProperty();
    void payRent(Player *receiving_player, const Property &property) const;
    void get_out_of_jail();
    void declare_bankruptcy() const;

    static void buyProperty(Player *player, const Property &property);

public:
    static constexpr int go_amount = 200;
    static constexpr int jail_exit_amount = 50;
    Game();

    /**
     * A vector of all the players in the game. This must be a subclass of the Player class (which is not instantiable),
     * such as UserPlayer or AiPlayer
     */
    std::vector<std::unique_ptr<Player>> players;
    /**
     * Starts the game loop
     */
    [[noreturn]] void play();
    /**
     * Rolls a standard 6 sided dice and returns the result.
     * @return The dice roll, from 1 to 6 (inclusive)
     */
    int rollDice();
};



#endif //GAME_H
