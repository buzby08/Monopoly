//
// Created by busby08 on 16/06/25.
//

#include "Game.h"
#include <iostream>
#include <string>

using namespace std;

Game::Game() {}


void Game::play() {
    const string red_text = "\033[31m";
    const string default_text = "\033[0m";

    cout << red_text << "The game is not ready to play yet" << default_text << endl;
    exit(-1);
}
