//
// Created by busby08 on 29/06/25.
//

#include "ChanceCards.h"

#include <fstream>
#include <iostream>

#include "AiPlayer.h"
#include "Game.h"
#include "Random.h"


std::string ChanceCards::_removeKeyword(const std::string &message, std::string keyword) {
    keyword = keyword + " ";

    if (!message.starts_with(keyword))
        throw std::invalid_argument("ChanceCards::_removeKeyword: Message does not start with keyword");
    return message.substr(keyword.size()+1, std::string::npos);
}

void ChanceCards::_advanceTo(std::string action, Player *player) {
    action = _removeKeyword(action, "ADVANCE");
    action = _removeKeyword(action, "space");

    int new_space = std::stoi(action);

    if (new_space < player->Space())
        new_space += Game::board.MaxBoardSpaces();

    const int space_difference = new_space - player->Space();

    player->move_forward(space_difference);
}

void ChanceCards::_actionId(std::string action, Player *player) {

}

void ChanceCards::_addMoney(std::string action, Player *player) {
    action = _removeKeyword(action, "ADD_MONEY");

    const int money = std::stoi(action);

    player->add_money(money);
}

void ChanceCards::_removeMoney(std::string action, Player *player) {
    action = _removeKeyword(action, "REMOVE_MONEY");

    const int money = std::stoi(action);

    player->remove_money(money);
}

void ChanceCards::_getOutOfJailFree(std::string action, Player *player) {
    action = _removeKeyword(action, "GET_OUT_OF_JAIL_FREE");
    player->add_get_out_of_jail_free();
}

void ChanceCards::_goToJail(std::string action, Player *player) {
    action = _removeKeyword(action, "GO_TO_JAIL");
    player->enter_jail();
}

void ChanceCards::_moveBack(std::string action, Player *player) {
    action = _removeKeyword(action, "MOVE_BACK");
    const int spaces_to_move = std::stoi(action);
    player->move_backward(spaces_to_move);
}

void ChanceCards::_advanceToNearestStation(Player *player) {

}

void ChanceCards::_advanceToNearestUtility(Player *player) {
}

void ChanceCards::_payEachPlayer(Player *current_player) {
    constexpr int money_to_pay = 50;

    for (const auto& player : Game::players) {
        if (player->Id() == current_player->Id()) continue;

        current_player->remove_money(money_to_pay);
        player->add_money(money_to_pay);
    }
}


json ChanceCards::readChanceCards(const std::string& file_path) {
    std::ifstream f(file_path);

    const json data = json::parse(f);

    json valid_data = json::array();

    AiPlayer test_player(0);

    for (auto & card : data) {
        try {
            doChanceCard(card, &test_player);
        } catch (std::invalid_argument& e) {
            std::cout << "Ignoring invalid chance card" << std::endl;
            continue;
        }

        valid_data.push_back(card);
    }

    return valid_data;
}

json ChanceCards::getChanceCard() {
    if (!_chance_cards.has_value()) {
        set_chance_cards(readChanceCards(chance_card_file_path));
    }

    constexpr int minimum_value = 0;
    const int maximum_value = static_cast<int>(_chance_cards->size()) - 1;

    const int chance_card_index = Random::getRandomInt(minimum_value, maximum_value);
    const json& chance_card = _chance_cards->at(chance_card_index);

    return chance_card;
}

void ChanceCards::doChanceCard(json chance_card, Player *player) {
    std::string text = chance_card["text"];
    std::string full_action = chance_card["action"];

    if (full_action.starts_with("ADVANCE")) {

    }
}


