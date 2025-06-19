#include <fstream>
#include <iostream>

#include "AiPlayer.h"
#include "UserPlayer.h"
#include "Game.h"

int main() {
    std::cout << "Welcome to Monopoly, using c++" << std::endl;

    Game game{};

    UserPlayer player_one(1);
    AiPlayer player_two(2);

    game.players.push_back(make_unique<UserPlayer>(player_one));
    game.players.push_back(make_unique<AiPlayer>(player_two));

    game.play();

    return 0;
}