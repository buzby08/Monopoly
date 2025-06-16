//
// Created by busby08 on 16/06/25.
//

#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>

#include "Player.h"
using namespace std;

class Game {
    int turn = 0;

public:
    Game();
    vector<unique_ptr<Player>> players;
    void play();
};



#endif //GAME_H
