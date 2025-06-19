//
// Created by busby08 on 16/06/25.
//

#include "Game.h"
#include <iostream>
#include <string>
#include <ctime>

#include "Board.h"
#include "input_utils.h"


Game::Game() {}

void Game::nextTurn() {
    if (turn >= players.size()-1) {
        turn = 0;
        return;
    }

    turn ++;
}


void Game::play() {
    start:
    clear_screen();

    for (int i = 0; i < players.size(); ++i) {
        std::cout << players[i]->current_state() << std::endl;
    }


    printf("It is player %d's turn\n", turn+1);
    printf("Click enter to roll the dice\n");
    std::cin.get();

    int dice_roll_one = rollDice();
    int dice_roll_two = rollDice();

    printf("You rolled a %d and a %d\n", dice_roll_one, dice_roll_two);
    players[turn]->move_forward(dice_roll_one+dice_roll_two);

    int current_space = players[turn]->Space();
    printf("You are on space %d\n", current_space);

    SpaceActions space_action = Board::get_space_action(current_space);
    doSpaceAction(space_action);

    nextTurn();
    goto start;
}

int Game::rollDice() {
    srand((unsigned)time(0));
    int i = (rand() % 6) + 1;
    return i;
}

void Game::doSpaceAction(const SpaceActions action) {
    switch (action) {
        case SpaceActions::Go:
            landOnGo();

        case SpaceActions::GoToJail:
            goToJail();

        case SpaceActions::Jail:
            onJailSpace();

        default:
            return;
    }
}

void Game::landOnGo() {
    printf("Player %d landed on Go. You will get $%d on your next move (when you pass go)\n", turn+1, go_amount);
}

void Game::goToJail() {
    printf("Player %d!\n", turn+1);
    printf("GO TO JAIL!\n");
    printf("Do NOT pass go!\n");
    printf("Do NOT collect $%d", go_amount);
    players[turn]->enter_jail();
}

void Game::onJailSpace() {
    if (!players[turn]->InJail()) return;


}
