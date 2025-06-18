//
// Created by busby08 on 16/06/25.
//

#ifndef BOARD_H
#define BOARD_H

#include <array>

#include "Property.h"

enum class SpaceActions {
    Go,
    Property,
    IncomeTax,
    CommunityChest,
    Chance,
    Station,
    FreeParking,
    Jail,
    LuxuryTax,
    GoToJail,
    Invalid
};

class Board {
private:
    std::array<Property, 22> properties;
    void populate_properties();

public:
    Board();

    static constexpr int jail_space = 10;
    static SpaceActions get_space_action(int space_number);
};



#endif //BOARD_H
