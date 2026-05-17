//
// Created by busby08 on 16/06/25.
//

#include "Game.h"

#include <csignal>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

#include "Ansi.h"
#include "ChanceCards.h"
#include "Logger.h"
#include "utilities.h"
#include "Random.h"

#include <readchar/library.h>

#include "Settings.h"


void Game::nextTurn() {
    if (turn >= players.size()-1) {
        turn = 0;
        return;
    }

    turn ++;
}

int Game::getPreviousPlayerTurnNumber() {
    const int previous_player_turn_number = turn - 1;

    if (previous_player_turn_number < 0)
        return static_cast<int>(players.size()) + previous_player_turn_number;

    return previous_player_turn_number;
}

void Game::setupFromFile(const std::string &settings_file_path) {
    const auto settings = Settings(settings_file_path);

    setupBoard(settings.BoardFilePath(), settings.PropertiesFilePath());
    go_amount = settings.GoAmount();
    jail_exit_amount = settings.JailExitAmount();
    roll_per_dice = settings.RollPerDice();

    players = settings.GetPlayers();

    constexpr int number_of_dice = 2;
    max_roll = roll_per_dice * number_of_dice;

}

[[noreturn]] void Game::play() {
    ChanceCards::readChanceCards(ChanceCards::chance_card_file_path);
    signal(SIGINT, signal_callback_handler);
    start:
    clear_screen(true);

    if (paused)
    {
        pauseMenu();
        goto start;
    }

    if (currentPlayer()->IsBankrupt()) {
        nextTurn();
        goto start;
    }

    doBankruptCheck();

   if (players.size() > 2)
        std::cout << players[getPreviousPlayerTurnNumber()]->current_state() << std::endl;

    std::cout << currentPlayer()->current_state() << std::endl;
    std::cout << players[getNextPlayerTurnNumber()]->current_state() << std::endl;


    if (currentPlayer()->InJail())
        getOutOfJail();

    if (currentPlayer()->InJail()) {
        nextTurn();
        goto start;
    }

    std::cout << currentPlayer()->Color();
    std::cout << std::format("It is player {}'s turn", turn+1) << std::endl;

    if (currentPlayer()->InJail()) {
        currentPlayer()->request_option("Click enter to take your turn\n");
        getOutOfJail();
    }

    if (currentPlayer()->InJail()) {
        nextTurn();
        goto start;
    }

    std::string additional_message;

    additional_message += "(s) Save game\n";
    additional_message += "(e) Save and exit\n";
    additional_message += "(b) Declare bankruptcy\n";
    additional_message += "(ENTER KEY) Roll dice\n";
    const char option = gameState(additional_message);

    Logger::info(std::format("Currently selected: {}", option));

    switch (option) {
        case 's':
            save_state();
            goto start;

        case 'e':
            save_state();
            exit(0);

        case 'b':
            declare_bankruptcy();
            nextTurn();
            goto start;

        case '\n':
            break;

        default:
            goto start;
    }


    clear_screen();
    Logger::info("Just cleared screen, about to roll dice");
    int dice_roll_one = rollDice();
    int dice_roll_two = rollDice();
    int total_roll = dice_roll_one + dice_roll_two;
    Logger::info(std::format("Rolled dice: {}, {}", dice_roll_one, dice_roll_two));
    printf("You rolled a %d and a %d\n\n", dice_roll_one, dice_roll_two);

    std::cout << std::format("You are currently on {}\n", board.get_space_string(currentPlayer()->Space()));
    std::cout << Ansi::reset << currentPlayer()->Color();

    int counter = 0;
    while (total_roll > 0)
    {
        counter++;
        currentPlayer()->move_forward(1);
        std::cout << std::format("Move {} - {}\n", counter, board.get_space_string(currentPlayer()->Space()));
        std::cout << Ansi::reset << currentPlayer()->Color();
        total_roll--;
        if (currentPlayer()->GetPlayerType() != PlayerType::Ai)
        {
            sleep(1);
        }

    }

    int current_space = currentPlayer()->Space();
    currentPlayer()->request_option("Click enter to continue\n");

    clear_screen();

    SpaceActions space_action = board.get_space_action(current_space);
    doSpaceAction(space_action);

    nextTurn();
    goto start;
}

Player* Game::get_player_with_id(const int id)
{
    for (int i = 0; i<players.size(); i++) {
        if (players[i]->Id() == id) return players[i].get();
    }
    
    return nullptr;
}

int Game::rollDice() {
    return Random::getRandomInt(1, roll_per_dice);
}

void Game::save_state(const std::string &save_file) {
    // clear_screen();
    // std::cout << "[WARNING] Save is currently disabled. The game has not been saved.\n";
    // currentPlayer()->request_option("Click any key to continue...\n");
    // return;

    std::ofstream file(save_file, std::ios::binary);
    cereal::BinaryOutputArchive archive(file);

    Logger::info("Before saving");

    archive(turn);
    archive(board);
    archive(go_amount);
    archive(jail_exit_amount);
    archive(roll_per_dice);
    archive(players);

    file.close();

    Logger::info("After saving");

    clear_screen();
    std::cout << "The game has been saved" << std::endl;
    currentPlayer()->request_option("Click any key to continue...\n");
}

void Game::load_state(const std::string &save_file) {
    // std::cout << "[WARNING] Load is currently disabled. The game has not been loaded.\n";
    // currentPlayer()->request_option("Click any key to continue...\n");
    // return;

    std::ifstream file(save_file, std::ios::binary);
    cereal::BinaryInputArchive archive(file);

    Logger::info("Before loading");

    archive(turn);
    archive(board);
    archive(go_amount);
    archive(jail_exit_amount);
    archive(roll_per_dice);
    archive(players);

    file.close();

    Logger::info("After loading");

    board.loadBoard();
}

void Game::passGo(Player *player) {
    std::cout << std::format("You passed go. Collect £{}", go_amount) << std::endl;
    player->request_option("Click enter to continue\n");
    player->add_money(go_amount);
}

void Game::pauseMenu() {
    pauseMenuStart:
    clear_screen(true);

    std::cout << "Select an option:" << std::endl;
    std::cout << "(s) Save game" << std::endl;
    std::cout << "(g) Show game state" << std::endl;
    std::cout << "(c) Continue" << std::endl;
    std::cout << "(e) Save and exit" << std::endl;

    char option = get_key_as_char(false);

    switch (option) {
        case 's':
            save_state();
            goto pauseMenuStart;

        case 'g':
            gameState("Click any key to return\n", true);
            goto pauseMenuStart;

        case 'c':
            signal(SIGINT, signal_callback_handler);
            paused = false;
            return;

        case 'e':
            save_state();
            exit(0);

        default:
            goto pauseMenuStart;
    }
}

void Game::endGame() {
    save_state();
    clear_screen(true);
    std::cout << "The game is over" << std::endl;

    std::vector<Player*> max_players;
    int max_score = 0;

    for (const auto & unique_player_ptr : players) {
        Player *player = unique_player_ptr.get();

        std::cout << Ansi::reset;

        if (player->IsBankrupt()) {
            std::cout << Ansi::red_fg;
            std::cout << std::format("Player {} went bankrupt. Final score £0\n", player->Id()) << std::endl;
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

    std::cout << Ansi::reset << std::endl;

    if (max_players.empty()) {
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

int Game::getNextPlayerTurnNumber() {
    const int current_player_turn_number = turn;
    nextTurn();
    const int next_player_turn_number = turn;

    turn = current_player_turn_number;
    return next_player_turn_number;
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

        case SpaceActions::Chance:
            chanceCard();
            return;

        default:
            return;
    }
}

Player * Game::currentPlayer() {
    return players[turn].get();
}

void Game::onProperty() {
    const int current_space = currentPlayer()->Space();

    try {
        const Property* current_property = board.get_space_property(current_space);

        if (current_property->owned() && current_property->owner() == currentPlayer()) return;
        if (current_property->owned()) {
            payRent(current_property->owner(), current_property);
            return;
        }

        buyProperty(currentPlayer(), current_property);

    } catch (std::invalid_argument &_) {
        printf("%sSystem Error (Game::onProperty): There has been a mismatch between the board properties and the current space.%s\n",
            Ansi::red_fg.c_str(), Ansi::reset.c_str());
        exit(-1);
    }
}

void Game::payRent(Player* receiving_player, const Property* property) {
    currentPlayer()->request_option(std::format(
        "Player {}, you must pay £{} rent to player {}\n",
        currentPlayer()->Id(),
        property->rent(),
        receiving_player->Id()));
    
    receiving_player->request_option(std::format(
        "Player {}, player {} has been asked to pay you £{}.\nClick enter to receive this.", receiving_player->Id(), currentPlayer()->Id(), property->rent()));

    std::cout << currentPlayer()->Color();
    currentPlayer()->remove_money(property->rent());
    receiving_player->add_money(property->rent());
}

void Game::getOutOfJail() {
    clear_screen(true);
    const GetOutOfJailOption get_out_of_jail_option = currentPlayer()->get_out_of_jail_option();

    switch (get_out_of_jail_option) {
        case GetOutOfJailOption::Pay:
            currentPlayer()->remove_money(jail_exit_amount);
            currentPlayer()->exit_jail();
            return;

        case GetOutOfJailOption::GetOutOfJailFree:
            currentPlayer()->remove_get_out_of_jail_free();
            currentPlayer()->exit_jail();
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
                currentPlayer()->reset_get_out_of_jail_attempts();
                currentPlayer()->exit_jail();
                return;
            }

            currentPlayer()->increase_get_out_of_jail_attempts();
            std::cout << "You did not get out of jail!" << std::endl;
            return;
    }
}

void Game::declare_bankruptcy() {
    clear_screen(true);
    std::cout << Ansi::red_fg;

    std::cout << std::format("Player {} has declared bankruptcy!", currentPlayer()->Id()) << std::endl;
    currentPlayer()->make_bankrupt();

    doBankruptCheck();
}

void Game::buyProperty(Player *player, const Property* property) {
    const bool player_wants_to_buy = player->buy_property(*property);

    if (!player_wants_to_buy) return;

    player->remove_money(property->cost());
    transfer_ownership(property, player);
}

void Game::chanceCard() {
    clear_screen();
    const json chance_card = ChanceCards::getChanceCard();
    std::cout << "You landed on a chance card." << std::endl;
    std::cout << chance_card.value("text", "No chance card text available") << std::endl;
    currentPlayer()->request_option("Click any key to continue...\n");
    ChanceCards::doChanceCard(chance_card, currentPlayer());
}

char Game::gameState(const std::string &additional_message, const bool force_from_user) {
    const int original_turn = turn;
    const int original_player_id = players[original_turn]->Id();
    gameStateStart:

    clear_screen();
    
    const bool previous_turn_is_original_turn = players[getPreviousPlayerTurnNumber()]->Id() == original_player_id;
    const bool current_turn_is_original_turn = currentPlayer()->Id() == original_player_id;
    const bool next_turn_is_original_turn = players[getNextPlayerTurnNumber()]->Id() == original_player_id;
    
    if (players.size() > 2 && previous_turn_is_original_turn) {
        std::cout << std::endl;
        std::cout << Ansi::red_fg << "--------------------------------------------" << Ansi::reset << std::endl;
    }
    if (players.size() > 2)
        std::cout << players[getPreviousPlayerTurnNumber()]->current_state() << std::endl;
    
    if (players.size() > 2 && previous_turn_is_original_turn) {
        std::cout << Ansi::red_fg << "--------------------------------------------" << Ansi::reset << std::endl;
        std::cout << std::endl;
    }

    if (current_turn_is_original_turn) {
        std::cout << std::endl;
        std::cout << Ansi::red_fg << "--------------------------------------------" << Ansi::reset << std::endl;
    }
    std::cout << currentPlayer()->current_state() << std::endl;
    if (current_turn_is_original_turn) {
        std::cout << Ansi::red_fg << "--------------------------------------------" << Ansi::reset << std::endl;
        std::cout << std::endl;
    }
    
    if (next_turn_is_original_turn) {
        std::cout << std::endl;
        std::cout << Ansi::red_fg << "--------------------------------------------" << Ansi::reset << std::endl;
    }
    std::cout << players[getNextPlayerTurnNumber()]->current_state() << std::endl;
    if (next_turn_is_original_turn) {
        std::cout << Ansi::red_fg << "--------------------------------------------" << Ansi::reset << std::endl;
        std::cout << std::endl;
    }

    std::cout << players[original_turn]->Color();

    std::cout << "Select an option:" << std::endl;
    std::cout << "Use the up and down arrow keys to show the player states" << std::endl;
    std::cout << additional_message << std::endl;

    std::string option;

    if (force_from_user) {
        option = readchar::readkey();
    } else {
        option = players[original_turn]->request_option("");
    }

    if (option == readchar::keys::ARR_UP) {
        turn = getPreviousPlayerTurnNumber();
        goto gameStateStart;
    }

    if (option == readchar::keys::ARR_DOWN) {
        nextTurn();
        goto gameStateStart;
    }

    turn = original_turn;
    return option[0];
}

void Game::doBankruptCheck() {
    int number_bankrupt = 0;
    for (const auto & player : players) {
        if (player->IsBankrupt()) number_bankrupt++;
    }

    if (number_bankrupt >= players.size() - 1)
        endGame();
}

void Game::transfer_ownership(const Property* property, Player* player)
{
    board.mark_owned(property->space(), player);
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
    currentPlayer()->request_option("Click enter to confirm\n");
    currentPlayer()->enter_jail();
}

void Game::onJailSpace() {
    if (!players[turn]->InJail()) return;
}
