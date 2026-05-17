//
// Created by busby08 on 15/06/25.
//

#include "utilities.h"
#include <iostream>
#include <string>
#include <limits>

#include "Ansi.h"
#include <readchar/library.h>

int get_int(const std::string &message, const int minimum_value, const int maximum_value, const bool minimum_used,
            const bool maximum_used) {
        start:
        std::cout << message << std::endl;

        std::string string_input = readchar::readkey();
        int value;

        try {
            value = std::stoi(string_input);
        } catch (const std::invalid_argument &e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You didnt enter an integer" << std::endl;
            goto start;
        }

        if (minimum_used && value < minimum_value) {
            std::cout << "You must enter a value greater than or equal to " << minimum_value << std::endl;
            goto start;
        }

        if (maximum_used && value > maximum_value) {
            std::cout << "You must enter a value less than or equal to " << maximum_value << std::endl;
            goto start;
        }

        return value;
}

int get_int(const std::string &message, const int limit, const LimitType limit_type) {
    switch (limit_type) {
        case LimitType::Min:
            return get_int(message, limit, 0, true, false);

        case LimitType::Max:
            return get_int(message, 0, limit, false, true);

        default:
            throw std::invalid_argument("An invalid limit type was passed to the function");
    }
}

int get_int(const std::string &message, int minimum_value, int maximum_value) {
    return get_int(message, minimum_value, maximum_value, true, true);
}

void clear_screen(const bool reset_color) {
    if (reset_color)
        std::cout << Ansi::reset;
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

std::vector<std::string> split_string(const std::string &message, char delimiter) {
    std::vector<std::string> values;

    std::string current_message;

    for (auto & character : message) {
        if (character == delimiter) {
            values.push_back(current_message);
            current_message = "";
            continue;
        }

        current_message += character;
    }

    values.push_back(current_message);

    return values;
}

std::string join_integers(const std::vector<int> &numbers) {
    std::string result;

    for (int i = 0; i < numbers.size(); i++) {
        if (i == (numbers.size() - 1)) {
            result += "and " + std::to_string(numbers[i]);
            continue;
        }

        result = result + std::to_string(numbers[i]) + ", ";
    }

    return result;
}

std::string get_key_as_string(bool catch_keyboard_interupt) {
    get_key_as_string_start:

    std::string input;

    if (!catch_keyboard_interupt) return readchar::readkey();

    try {
        input = readchar::readkey();
    } catch (const readchar::exceptions::KeyboardInterrupt &e) {
        signal_callback_handler(0);
    }

    return input;
}

char get_key_as_char(bool catch_keyboard_interupt) {
    get_key_as_char_start:

    std::string input = get_key_as_string(catch_keyboard_interupt);

    if (input.size() != 1) {
        std::cout << "Please click a valid key" << std::endl;
        goto get_key_as_char_start;
    }

    return input[0];
}

