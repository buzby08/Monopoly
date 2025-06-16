//
// Created by busby08 on 16/06/25.
//

#include <string>
#include "UserPlayer.h"
#include "Property.h"
#include "input_utils.h"

using namespace std;

GetOutOfJailOption UserPlayer::get_out_of_jail_option() {
    int optionNumber = 0;
    GetOutOfJailOption valid_options[] = {};

    if (get_out_of_jail_free) {
        optionNumber++;
        cout << format("{}. Use get out of jail free card.", optionNumber) << endl;
        valid_options[optionNumber-1] = GetOutOfJailOption::GetOutOfJailFree;
    }

    if (money > 50) {
        optionNumber++;
        cout << format("{}. Pay $50.", optionNumber) << endl;
        valid_options[optionNumber-1] = GetOutOfJailOption::Pay;
    }

    if (get_out_of_jail_attempts < 3) {
        optionNumber++;
        cout << format("{}. Roll a double.", optionNumber) << endl;
        valid_options[optionNumber-1] = GetOutOfJailOption::DiceRoll;
    }

    optionNumber++;
    cout << format("{}. Declare bankruptcy.", optionNumber) << endl;
    valid_options[optionNumber-1] = GetOutOfJailOption::DeclareBankruptcy;

    int selected_option = get_int("Enter an option: ", 1, optionNumber+1);
    return valid_options[selected_option-1];
}

bool UserPlayer::buy_property(Property property) {
    if (money < property.price()) {
        printf("You cannot buy %s, as it costs $%d, but you only have $%d",
            property.c_name(), property.price(), money);
        return false;
    }

    printf("Would you like to buy %s for $%d?\n", property.c_name(), property.price());
    printf("1. Yes.\n");
    printf("2. No.\n");
    const int selected_option = get_int("Enter an option: ", 1, 2);

    return selected_option == 1;
}
