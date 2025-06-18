//
// Created by busby08 on 15/06/25.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

#include "Property.h"

enum class PlayerType { User, Ai };
enum class GetOutOfJailOption { Pay, DiceRoll, GetOutOfJailFree, DeclareBankruptcy };

class Player {
protected:
    const PlayerType player_type;
    int id;
    std::string color;
    int space;
    int money;
    int get_out_of_jail_attempts;
    bool get_out_of_jail_free;
    std::vector<Property> properties;
    bool in_jail = false;
public:
    explicit Player(int id);
    explicit Player(int id, std::string color);
    explicit Player(const std::string &save_file_path);
    virtual ~Player() = default;

    void add_money(int amount);
    void remove_money(int amount);

    void enter_jail();
    void exit_jail();

    void move_to_space(int new_space);
    int move_forward(int number_of_spaces);
    std::string as_string();
    std::string current_state();

    int Space();
    bool InJail();

    virtual GetOutOfJailOption get_out_of_jail_option() = 0;
    virtual bool buy_property(Property property) = 0;

};



#endif //PLAYER_H
