//
// Created by busby08 on 16/06/25.
//

#include "Game.h"

#include <csignal>
#include <iostream>
#include <string>
#include <ctime>

#include "Ansi.h"
#include "Board.h"
#include "utilities.h"
#include "Random.h"


void Game::nextTurn() {
    if (turn >= players.size()-1) {
        turn = 0;
        return;
    }

    turn ++;
}


[[noreturn]] void Game::play() {
    signal(SIGINT, signal_callback_handler);

    start:
    clear_screen(true);

    for (const auto & player : players) {
        std::cout << player->current_state() << std::endl;
    }


    if (current_player()->InJail())
        get_out_of_jail();

    if (current_player()->InJail()) {
        nextTurn();
        goto start;
    }

    std::cout << current_player()->Color();
    std::cout << std::format("It is player {}'s turn", turn+1) << std::endl;

    if (current_player()->InJail()) {
        current_player()->request_enter("Click enter to take your turn\n");
        get_out_of_jail();
    }

    if (current_player()->InJail()) {
        nextTurn();
        goto start;
    }

    current_player()->request_enter("Click enter to roll the dice\n");

    clear_screen();

    int dice_roll_one = rollDice();
    int dice_roll_two = rollDice();

    printf("You rolled a %d and a %d\n", dice_roll_one, dice_roll_two);
    current_player()->move_forward(dice_roll_one+dice_roll_two);

    int current_space = current_player()->Space();
    printf("You are on space %d\n", current_space);
    current_player()->request_enter("Click enter to continue\n");

    clear_screen();

    SpaceActions space_action = board.get_space_action(current_space);
    doSpaceAction(space_action);

    nextTurn();
    goto start;
}

int Game::rollDice() {
    return Random::getRandomInt(1, 6);
}

void Game::passGo(Player *player) {
    std::cout << std::format("You passed go. Collect £{}", go_amount) << std::endl;
    player->request_enter("Click enter to continue\n");
    player->add_money(go_amount);
}

void Game::endGame(const bool ignore_player, const int player_to_ignore) {
    std::cout << "The game is over" << std::endl;

    std::vector<Player*> max_players;
    int max_score = 0;

    for (const auto & unique_player_ptr : players) {
        Player *player = unique_player_ptr.get();

        std::cout << Ansi::reset;

        if (ignore_player && player->Id() == player_to_ignore) {
            std::cout << Ansi::red_fg;
            std::cout << std::format("Player {} went bankrupt. Final score £0", player->Id()) << std::endl;
            continue;
        }

        std::cout << player->Color();
        int player_score = player->calculate_score();
        std::cout << std::format("Player {} has a score of £{}", player->Id(), player_score) << std::endl;

        if (player_score > max_score) {
            max_score = player_score;
            max_players.clear();
            max_players.push_back(player);
            continue;
        }

        if (player_score == max_score) {
            max_players.push_back(player);
        }
    }

    std::cout << Ansi::reset;

    if (max_players.size() <= 0) {
        std::cout << std::endl << "There is no winner" << std::endl;
    }

    if (max_players.size() == 1) {
        std::cout << max_players[0]->Color();
        std::cout << std::format("Player {} wins with a score of £{}", max_players[0]->Id(), max_score) << std::endl;
    }

    if (max_players.size() >= 2) {
        std::cout << std::endl;

        std::vector<int> winning_ids;
        for (const auto & player : max_players) {
            winning_ids.push_back(player->Id());
        }

        std::cout << std::format(
            "There are {} winners, players {}, with a score of £{} each",
            winning_ids.size(),
            join_integers(winning_ids),
            max_score);
        std::cout << std::endl;
    }

    std::cout << Ansi::reset;
    exit(0);
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

Player * Game::current_player() {
    return players[turn].get();
}

void Game::onProperty() {
    const int current_space = current_player()->Space();

    try {
        Property current_property = board.get_space_property(current_space);

        if (current_player()->has_property(current_property)) return;

        for (const auto & player : players) {
            if (player->Id() == current_player()->Id()) { continue; }

            if (player->has_property(current_property)) {
                payRent(player.get(), current_property);
                return;
            }
        }

        buyProperty(current_player(), current_property);

    } catch (std::invalid_argument &_) {
        printf("%sSystem Error (Game::onProperty): There has been a mismatch between the board properties and the current space.%s\n",
            Ansi::red_fg.c_str(), Ansi::reset.c_str());
        exit(-1);
    }
}

void Game::payRent(Player *receiving_player, const Property &property) {
    current_player()->request_enter(std::format(
        "Player {}, you must pay £{} rent to player {}\n",
        current_player()->Id(),
        property.rent(),
        receiving_player->Id()));

    current_player()->remove_money(property.rent());
    receiving_player->add_money(property.rent());
}

void Game::get_out_of_jail() {
    clear_screen(true);
    const GetOutOfJailOption get_out_of_jail_option = current_player()->get_out_of_jail_option();

    switch (get_out_of_jail_option) {
        case GetOutOfJailOption::Pay:
            current_player()->remove_money(jail_exit_amount);
            current_player()->exit_jail();
            return;

        case GetOutOfJailOption::GetOutOfJailFree:
            current_player()->remove_get_out_of_jail_free();
            current_player()->exit_jail();
            return;

        case GetOutOfJailOption::DeclareBankruptcy:
            declare_bankruptcy();
            exit(0);

        case GetOutOfJailOption::DiceRoll:
            int dice_roll_one = rollDice();
            int dice_roll_two = rollDice();

            std::cout << std::format("You rolled a {} and a {}", dice_roll_one, dice_roll_two) << std::endl;
            if (dice_roll_one == dice_roll_two) {
                std::cout << "You got out of jail!" << std::endl;
                current_player()->reset_get_out_of_jail_attempts();
                current_player()->exit_jail();
                return;
            }

            current_player()->increase_get_out_of_jail_attempts();
            std::cout << "You did not get out of jail!" << std::endl;
            return;
    }
}

void Game::declare_bankruptcy() {
    clear_screen(true);
    std::cout << Ansi::red_fg;

    std::cout << std::format("Player {} has declared bankruptcy!", current_player()->Id()) << std::endl;
    endGame(true, current_player()->Id());
}

void Game::buyProperty(Player *player, const Property &property) {
    const bool player_wants_to_buy = player->buy_property(property);

    if (!player_wants_to_buy) return;

    player->remove_money(property.cost());
    player->add_property(property);
}


void Game::landOnGo() {
    std::cout << std::format("You landed on go. Here is £{}!", go_amount) << std::endl;
    players[turn]->add_money(go_amount);
}

void Game::goToJail() {
    clear_screen();
    printf("Player %d!\n", turn+1);
    printf("GO TO JAIL!\n");
    printf("Do NOT pass go!\n");
    printf("Do NOT collect $%d\n", go_amount);
    current_player()->request_enter("Click enter to confirm\n");
    current_player()->enter_jail();
}

void Game::onJailSpace() {
    if (!players[turn]->InJail()) return;


}
