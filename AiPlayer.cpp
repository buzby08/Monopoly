//
// Created by busby08 on 16/06/25.
//

#include "AiPlayer.h"
#include "Property.h"

GetOutOfJailOption AiPlayer::get_out_of_jail_option() {
    if (get_out_of_jail_free) return GetOutOfJailOption::GetOutOfJailFree;

    constexpr int get_out_of_jail_price = 50;
    if (money > (get_out_of_jail_price * 2)) return GetOutOfJailOption::Pay;

    if (constexpr int dice_roll_limit = 3; get_out_of_jail_attempts < dice_roll_limit)
        return GetOutOfJailOption::DiceRoll;

    return GetOutOfJailOption::DeclareBankruptcy;
}

bool AiPlayer::buy_property(Property property) {
    if (money > (property.price()*2.5)) return true;

    return false;
}

