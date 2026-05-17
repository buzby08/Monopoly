//
// Created by busby08 on 29/06/25.
//

#ifndef CHANCECARDS_H
#define CHANCECARDS_H

#include <string>
#include <nlohmann/json.hpp>

#include "Player.h"

using json = nlohmann::json;

class ChanceCards {
    inline static std::optional<json> _chance_cards;

    static std::string _removeKeyword(const std::string &message, std::string keyword);

    static void _advanceTo(std::string action, Player* player);
    static void _actionId(std::string action, Player* player);
    static void _addMoney(std::string action, Player* player);
    static void _removeMoney(std::string action, Player* player);
    static void _getOutOfJailFree(std::string action, Player* player);
    static void _goToJail(std::string action, Player* player);
    static void _moveBack(std::string action, Player* player);
    static void _advanceToNearestStation(Player* player);
    static void _advanceToNearestUtility(Player* player);
    // static void _upgradesOnBuildings(Player* player);
    static void _payEachPlayer(Player* current_player);

public:
    inline static std::string chance_card_file_path = "chance_cards.json";

    static json readChanceCards(const std::string& file_path);
    static void doChanceCard(json chance_card, Player* player);
    static json getChanceCard();

    static void set_chance_cards(const json &chance_cards) {
        _chance_cards = chance_cards;
    }
};



#endif //CHANCECARDS_H
