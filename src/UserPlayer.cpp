//
// Created by busby08 on 16/06/25.
//

#include <string>
#include "UserPlayer.h"
#include "Property.h"
#include "utilities.h"

#include <readchar/library.h>


GetOutOfJailOption UserPlayer::get_out_of_jail_option() {
    int optionNumber = 0;
    std::vector<GetOutOfJailOption> valid_options;

    std::cout << std::format("{}You are in jail", color) << std::endl;

    if (get_out_of_jail_free) {
        optionNumber++;
        std::cout << format("{}. Use get out of jail free card.", optionNumber) << std::endl;
        valid_options.push_back(GetOutOfJailOption::GetOutOfJailFree);
    }

    if (money > 50) {
        optionNumber++;
        std::cout << format("{}. Pay $50.", optionNumber) << std::endl;
        valid_options.push_back(GetOutOfJailOption::Pay);
    }

    if (get_out_of_jail_attempts < 3) {
        optionNumber++;
        std::cout << format("{}. Roll a double.", optionNumber) << std::endl;
        valid_options.push_back(GetOutOfJailOption::DiceRoll);
    }

    optionNumber++;
    std::cout << format("{}. Declare bankruptcy.", optionNumber) << std::endl;
    valid_options.push_back(GetOutOfJailOption::DeclareBankruptcy);

    int selected_option = get_int("Enter an option: ", 1, optionNumber+1);
    return valid_options[selected_option-1];
}

bool UserPlayer::buy_property(Property property) {
    if (money < property.cost()) {
        clear_screen();
        printf("You cannot buy %s, as it costs $%d, but you only have $%d\n",
            property.c_name(), property.cost(), money);
        request_option("Click enter to continue\n");
        return false;
    }

    printf("Would you like to buy %s%s for $%d?\n", Game::board.get_space_string(property.space()).c_str(), color.c_str(), property.cost());
    printf("You have £%d\n", money);
    printf("1. Yes.\n");
    printf("2. No.\n");
    const int selected_option = get_int("Enter an option: ", 1, 2);

    return selected_option == 1;
}

std::string UserPlayer::request_option(const std::string &message) {
    std::cout << color << message;
    return get_key_as_string();
}
