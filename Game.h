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
    vector<unique_ptr<Player>> players;
    void play();
    static int rollDice();
};



#endif //GAME_H
