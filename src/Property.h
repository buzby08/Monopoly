//
// Created by busby08 on 16/06/25.

#ifndef PROPERTY_H
#define PROPERTY_H
#include <format>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class Player;

/**
 * All the color sets in the game
 */
enum class PropertyColorSet { Brown, LightBlue, Pink, Orange, Red, Yellow, Green, DarkBlue, Invalid };

inline std::string propertyColorSet_to_string(PropertyColorSet e) {
    switch (e) {
        case PropertyColorSet::Brown: return "Brown";
        case PropertyColorSet::LightBlue: return "Light Blue";
        case PropertyColorSet::Pink: return "Pink";
        case PropertyColorSet::Orange: return "Orange";
        case PropertyColorSet::Red: return "Red";
        case PropertyColorSet::Yellow: return "Yellow";
        case PropertyColorSet::Green: return "Green";
        case PropertyColorSet::DarkBlue: return "Dark Blue";

        case PropertyColorSet::Invalid:
        default:
            return "Invalid";
    }
}

inline PropertyColorSet propertyColorSet_from_string(const std::string &e) {
    if (e == "brown") return PropertyColorSet::Brown;
    if (e == "light_blue") return PropertyColorSet::LightBlue;
    if (e == "pink") return PropertyColorSet::Pink;
    if (e == "orange") return PropertyColorSet::Orange;
    if (e == "red") return PropertyColorSet::Red;
    if (e == "yellow") return PropertyColorSet::Yellow;
    if (e == "green") return PropertyColorSet::Green;
    if (e == "dark_blue") return PropertyColorSet::DarkBlue;

    return PropertyColorSet::Invalid;
}

struct PropertyStruct {
    std::string name;
    PropertyColorSet colour_group;
    int space;
    int cost;
    int mortgage;
    int base_rent;
    int rent_1;
    int rent_2;
    int rent_3;
    int rent_4;
    int hotel_rent;

    void set_value(const std::string& key, const int value) {
        if (key == "cost") {
                cost = value;
                return;
        }
        if (key == "mortgage") {
                mortgage = value;
                return;
        }
        if (key == "space") {
            space = value;
            return;
        }
        if (key == "base_rent") {
                base_rent = value;
                return;
        }
        if (key == "rent_1") {
                rent_1 = value;
                return;
        }
        if (key == "rent_2") {
                rent_2 = value;
                return;
        }
        if (key == "rent_3") {
                rent_3 = value;
                return;
        }
        if (key == "rent_4") {
                rent_4 = value;
                return;
        }
        if (key == "hotel_rent") {
                hotel_rent = value;
                return;
        }

        throw std::invalid_argument(std::format("PropertyStruct::set_value: Invalid key name '{}'", key));

    }

    void set_value(const std::string& key, const std::string& value) {
        if (key == "name") {
            name = value;
            return;
        }
        if (key == "color_group") {
            colour_group = propertyColorSet_from_string(value);
            return;
        }

        throw std::invalid_argument(std::format("PropertyStruct::set_value: Invalid key name - '{}'", key));
    }

};

class Property {
    std::string _name;
    int _cost;
    int _space;
    PropertyColorSet _color_set;
    int _number_of_houses = 0;
    bool _has_a_hotel = false;
    int _base_rent;
    int _rent_one_house;
    int _rent_two_houses;
    int _rent_three_houses;
    int _rent_four_houses;
    int _rent_hotel;
    int _mortgage;
    bool _owned = false;
    Player* _owner = nullptr;
    int _owner_id = -1;

public:
    Property(const std::string &name, int cost, int space, int site, int one_house, int two_house, int three_house, int four_house,
        int hotel, PropertyColorSet color_set);

    explicit Property(const PropertyStruct& data);
    explicit Property();

    [[nodiscard]] std::string name() const;

    const char *c_name();
    [[nodiscard]] int cost() const;
    [[nodiscard]] PropertyColorSet color_set() const;
    [[nodiscard]] int rent() const;
    [[nodiscard]] int space() const;
    [[nodiscard]] bool owned() const;
    [[nodiscard]] Player* owner() const;
    [[nodiscard]] int owner_id() const;

    void addHouse(int number_of_houses=1);

    std::string output();

    void set_owner(Player* new_owner);

    [[nodiscard]] std::string get_name_and_color_string(std::string previousColour = "") const;

    bool operator==(std::vector<Property>::const_reference property) const;

    template <class Archive>
    void serialize(Archive &ar);
};

template <class Archive>
void Property::serialize(Archive& ar)
{
    ar(_name, _cost, _space, _color_set, _number_of_houses, _has_a_hotel, _base_rent, _rent_one_house, _rent_two_houses, _rent_three_houses, _rent_four_houses, _rent_hotel, _mortgage, _owned, _owner_id);
}


#endif //PROPERTY_H
