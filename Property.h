//
// Created by busby08 on 16/06/25.

#ifndef PROPERTY_H
#define PROPERTY_H
#include <string>

/**
 * All the color sets in the game
 */
enum class PropertyColorSet { Brown, LightBlue, Pink, Orange, Red, Yellow, Green, DarkBlue };

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
        default: return "unknown";
    }
}

class Property {
private:
    std::string _name;
    int _price;
    PropertyColorSet _color_set;

public:
    Property(const std::string &name, int price, PropertyColorSet color_set);

    [[nodiscard]] std::string name() const;

    const char *c_name();
    [[nodiscard]] int price() const;
    [[nodiscard]] PropertyColorSet color_set() const;
};



#endif //PROPERTY_H
