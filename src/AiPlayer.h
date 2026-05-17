//
// Created by busby08 on 16/06/25.
//

#ifndef AiPlayer_H
#define AiPlayer_H

#include "Player.h"
#include "Property.h"


class AiPlayer final : public Player{
    void wait() const;
public:
    using Player::Player;

    ~AiPlayer() override = default;

    GetOutOfJailOption get_out_of_jail_option() override;
    bool buy_property(Property property) override;

    std::string request_option(const std::string &message) override;
    void use_delay();
};



#endif //AiPlayer_H
