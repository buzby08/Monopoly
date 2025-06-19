//
// Created by busby08 on 16/06/25.
//

#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>

#include "Board.h"
#include "Player.h"
using namespace std;

class Game {
    static constexpr int go_amount = 200;

    int turn = 0;
    void nextTurn();
    void doSpaceAction(SpaceActions action);

    void landOnGo();
    void goToJail();
    void onJailSpace();

public:
    Game();

    /**
     * A vector of all the players in the game. This must be a subclass of the Player class (which is not instantiable),
     * such as UserPlayer or AiPlayer
     */
    vector<unique_ptr<Player>> players;
    /**
     * Starts the game loop
     */
    void play();
    /**
     * Rolls a standard 6 sided dice and returns the result.
     * @return The dice roll, from 1 to 6 (inclusive)
     */
    static int rollDice();
};



#endif //GAME_H
