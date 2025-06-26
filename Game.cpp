//
// Created by busby08 on 16/06/25.
//

#include "Game.h"
#include <iostream>
#include <string>
#include <ctime>
#include <random>

#include "Ansi.h"
#include "Board.h"
#include "input_utils.h"


Game::Game() {
    board = Board();
    std::random_device rd;
    std::mt19937 gen(rd());

    mersenne_twister_engine = gen;

    std::uniform_int_distribution<> distrib(1, 6);
    random = distrib;
}

void Game::nextTurn() {
    if (turn >= players.size()-1) {
        turn = 0;
        return;
    }

    turn ++;
}


[[noreturn]] void Game::play() {
    start:
    clear_screen(true);

    for (int i = 0; i < players.size(); ++i) {
        std::cout << players[i]->current_state(board) << std::endl;
    }

    Player *current_player = players[turn].get();

    if (current_player->InJail())
        get_out_of_jail();

    if (current_player->InJail()) {
        nextTurn();
        goto start;
    }

    printf(current_player->Color().c_str());
    printf("It is player %d's turn\n", turn+1);

    if (current_player->InJail()) {
        current_player->request_enter("Click enter to take your turn\n");
        get_out_of_jail();
    }

    if (current_player->InJail()) {
        nextTurn();
        goto start;
    }

    current_player->request_enter("Click enter to roll the dice\n");

    clear_screen();

    int dice_roll_one = rollDice();
    int dice_roll_two = rollDice();

    printf("You rolled a %d and a %d\n", dice_roll_one, dice_roll_two);
    current_player->move_forward(dice_roll_one+dice_roll_two);

    int current_space = current_player->Space();
    printf("You are on space %d\n", current_space);
    current_player->request_enter("Click enter to continue\n");

    clear_screen();

    SpaceActions space_action = board.get_space_action(current_space);
    doSpaceAction(space_action);

    nextTurn();
    goto start;
}

int Game::rollDice() {
    return random(mersenne_twister_engine);
}

void Game::doSpaceAction(const SpaceActions action) {
    switch (action) {
        case SpaceActions::Go:
            landOnGo();
            return;

        case SpaceActions::GoToJail:
            goToJail();
            return;

        case SpaceActions::Jail:
            onJailSpace();
            return;

        case SpaceActions::Property:
            onProperty();
            return;

        default:
            return;
    }
}

void Game::onProperty() {
    Player *current_player = players[turn].get();
    const int current_space = current_player->Space();

    try {
        Property current_property = board.get_space_property(current_space);

        if (current_player->has_property(current_property)) return;

        for (const auto & player : players) {
            if (player->Id() == current_player->Id()) { continue; }

            if (player->has_property(current_property)) {
                payRent(player.get(), current_property);
                return;
            }
        }

        buyProperty(current_player, current_property);

    } catch (std::invalid_argument &e) {
        printf("%sSystem Error (Game::onProperty): There has been a mismatch between the board properties and the current space.%s\n",
            Ansi::red_fg.c_str(), Ansi::reset.c_str());
        exit(-1);
    }
}

void Game::payRent(Player *receiving_player, const Property &property) const {
    Player *current_player = players[turn].get();

    current_player->request_enter(std::format(
        "Player {}, you must pay £{} rent to player {}\n",
        current_player->Id(),
        property.rent(),
        receiving_player->Id()));

    current_player->remove_money(property.rent());
    receiving_player->add_money(property.rent());
}

void Game::get_out_of_jail() {
    clear_screen(true);
    Player *current_player = players[turn].get();
    GetOutOfJailOption get_out_of_jail_option = current_player->get_out_of_jail_option();

    switch (get_out_of_jail_option) {
        case GetOutOfJailOption::Pay:
            current_player->remove_money(jail_exit_amount);
            current_player->exit_jail();
            return;

        case GetOutOfJailOption::GetOutOfJailFree:
            current_player->remove_get_out_of_jail_free();
            current_player->exit_jail();
            return;

        case GetOutOfJailOption::DeclareBankruptcy:
            declare_bankruptcy(current_player);
            exit(0);

        case GetOutOfJailOption::DiceRoll:
            int dice_roll_one = rollDice();
            int dice_roll_two = rollDice();

            std::cout << std::format("You rolled a {} and a {}", dice_roll_one, dice_roll_two) << std::endl;
            if (dice_roll_one == dice_roll_two) {
                std::cout << "You got out of jail!" << std::endl;
                current_player->reset_get_out_of_jail_attempts();
                current_player->exit_jail();
                return;
            }

            current_player->increase_get_out_of_jail_attempts();
            std::cout << "You did not get out of jail!" << std::endl;
            return;
    }
}

void Game::declare_bankruptcy(const Player *current_player) const {
    clear_screen(true);
    std::cout << Ansi::red_fg;

    std::cout << std::format("Player {} has declared bankruptcy!", current_player->Id()) << std::endl;
    std::cout << "The game is over" << std::endl;

    for (int i=0; i < players.size(); i++) {
        Player *player = players[i].get();

        if (player->Id() == current_player->Id()) continue;

        std::cout << std::format("Player {} has a score of £{}", player->Id(), player->calculate_score()) << std::endl;
    }

    std::cout << Ansi::reset;
    exit(0);
}

void Game::buyProperty(Player *player, const Property &property) {
    const bool player_wants_to_buy = player->buy_property(property);

    if (!player_wants_to_buy) return;

    player->remove_money(property.cost());
    player->add_property(property);
}


void Game::landOnGo() {
    printf("Player %d landed on Go. You will get $%d on your next move (when you pass go)\n", turn+1, go_amount);
}

void Game::goToJail() {
    Player *current_player = players[turn].get();

    clear_screen();
    printf("Player %d!\n", turn+1);
    printf("GO TO JAIL!\n");
    printf("Do NOT pass go!\n");
    printf("Do NOT collect $%d\n", go_amount);
    current_player->request_enter("Click enter to confirm\n");
    current_player->enter_jail();
}

void Game::onJailSpace() {
    if (!players[turn]->InJail()) return;


}
