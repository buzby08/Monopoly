#include <fstream>
#include <stdio.h>

#include "AiPlayer.h"
#include "Ansi.h"
#include "UserPlayer.h"
#include "Game.h"

int main() {
    printf("Welcome to Monopoly, using c++\n");

    Game game{};

    UserPlayer player_one(1, Ansi::cyan_fg);
    AiPlayer player_two(2, Ansi::green_fg);
    AiPlayer player_three(3, Ansi::yellow_fg);

    player_two.use_delay();
    player_three.use_delay();

    game.players.push_back(make_unique<UserPlayer>(player_one));
    game.players.push_back(make_unique<AiPlayer>(player_two));
    game.players.push_back(make_unique<AiPlayer>(player_three));

    game.play();

    return 0;
}