//
// Created by busby08 on 15/06/25.
//

#include "input_utils.h"
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>

using namespace std;


int get_int(const std::string &message, const int minimum_value, const int maximum_value, const bool minimum_used,
    const bool maximum_used) {
        start:
        cout << message << endl;

        int value;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You didnt enter an integer" << endl;
            goto start;
        }

        if (minimum_used && value < minimum_value) {
            cout << "You must enter a value greater than or equal to " << minimum_value << endl;
            goto start;
        }

        if (maximum_used && value > maximum_value) {
            cout << "You must enter a value less than or equal to " << maximum_value << endl;
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

void clear_screen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

