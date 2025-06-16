//
// Created by busby08 on 16/06/25.
//

#ifndef USERPLAYER_H
#define USERPLAYER_H
#include <format>
#include <iostream>

#include "Player.h"
#include "Property.h"

using namespace std;

class UserPlayer : public Player {
public:
    using Player::Player;

    ~UserPlayer() override = default;

    GetOutOfJailOption get_out_of_jail_option() override;
    bool buy_property(Property property) override;
};



#endif //USERPLAYER_H
