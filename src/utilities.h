//
// Created by busby08 on 15/06/25.
//

#ifndef UTILITIES_H
#define UTILITIES_H
#include <csignal>
#include <iostream>
#include <string>
#include <vector>

#include "Game.h"

enum class LimitType { Min, Max };

/**
 * Gets an integer from the user, ensuring it meets a set of rules
 * @param message The message to output to the user, before asking for an integer
 * @param minimum_value The minimum value that the user can enter
 * @param maximum_value The maximum value that the user can enter
 * @param minimum_used Will the 'minimum_value' rule be enforced?
 * @param maximum_used Will the 'maximum_value' rule be enforced?
 * @return The valid integer
 */
int get_int(const std::string& message, int minimum_value, int maximum_value, bool minimum_used, bool maximum_used);
/**
 * Gets an integer from the user, ensuring it meets either a minimum value or a maximum value
 * @param message The message to output to the user, before asking for an integer
 * @param limit The minimum value or the maximum value (cannot be both)
 * @param limit_type Specifies whether the limit provided is a minimum or maximum value
 * @return The valid integer
 */
int get_int(const std::string& message, int limit, LimitType limit_type);
/**
 * Gets an integer from the user, ensuring it meets either a minimum value or a maximum value
 * @param message The message to output to the user, before asking for an integer
 * @param minimum_value The minimum value that the user can enter
 * @param maximum_value The maximum value that the user can enter
 * @return The valid integer
 */
int get_int(const std::string& message, int minimum_value, int maximum_value);

/**
 * Clears the terminal screen, using a syscall (either the 'cls' command on Windows, or 'clear' on unix based systems
 */
void clear_screen(bool reset_color = false);

std::vector<std::string> split_string(const std::string& message, char delimiter);

std::string join_integers(const std::vector<int> &numbers);

inline void signal_callback_handler(const int signum) {
    signal(SIGINT, SIG_DFL);
    Game::paused = true;
}

std::string get_key_as_string(bool catch_keyboard_interupt = true);
char get_key_as_char(bool catch_keyboard_interupt = true);

#endif //UTILITIES_H
