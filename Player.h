//
// Created by busby08 on 15/06/25.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

#include "Board.h"
#include "Property.h"

enum class PlayerType { User, Ai };
/**
 * The options for getting out of jail
 */
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
    /**
     * Creates a blank instance of the player class, setting a custom id
     * @param id The players id
     */
    explicit Player(int id);
    /**
     * Creates a blank instance of the player class, setting a custom id and output color
     * @param id The players id
     * @param color The color that the player's information will be displayed in (as an ansi string)
     */
    explicit Player(int id, std::string color);
    /**
     * Creates an instance of the player class, loading the details from a json save file
     * @param save_file_path The file path containing the players save file
     */
    explicit Player(const std::string &save_file_path);
    virtual ~Player() = default;

    /**
     * Adds money to the players bank
     * @param amount The amount of money to add to the player
     */
    void add_money(int amount);
    /**
     * Removes money from the players bank
     * @param amount The amount of money to remove from the player
     */
    void remove_money(int amount);

    void add_property(const Property &property);
    void remove_property(const Property& property);
    bool has_property(const Property& property);

    void reset_get_out_of_jail_attempts();
    void increase_get_out_of_jail_attempts();

    /**
     * Moves the player to jail, and sets the in_jail modifier to true
     */
    void enter_jail();
    /**
     * Deactivates the in_jail modifier, thus removing the player from jail
     */
    void exit_jail();

    /**
     * Moves the player directly to a given space, skipping any 'movement' modifiers, such as passing go
     * @param new_space The new space that the player is on
     */
    void move_to_space(int new_space);
    /**
     * Moves the player around the board, by a select number of spaces. Applies any movement modifiers, such as passing
     * go
     * @param number_of_spaces The number of spaces forward that the player should move
     * @return The new space the player is on
     */
    int move_forward(int number_of_spaces);

    void remove_get_out_of_jail_free();

    int calculate_score();

    std::string as_string();
    /**
     * Gets the current state of the player, in a human-readable format
     * @return The current state of the player, for the game to output
     */
    std::string current_state(Board& board);

    /**
     * @return The current space variable
     */
    int Space();
    /**
     * @return The current in_jail variable
     */
    [[nodiscard]] bool InJail() const;
    /**
     * @return The current color variable
     */
    [[nodiscard]] std::string Color() const;
    int Id() const { return id; }
    int GetOutOfJailAttempts() const;

    virtual GetOutOfJailOption get_out_of_jail_option() = 0;
    virtual bool buy_property(Property property) = 0;
    virtual void request_enter(const std::string &message) = 0;

};



#endif //PLAYER_H
