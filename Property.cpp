//
// Created by busby08 on 16/06/25.
//

#include "Property.h"
#include <string>


std::string colorSetToString(const PropertyColorSet colorSet) {
    switch (colorSet) {
        case PropertyColorSet::Brown: return "Brown";
        case PropertyColorSet::LightBlue: return "Light Blue";
        case PropertyColorSet::Pink: return "Pink";
        case PropertyColorSet::Orange: return "Orange";
        case PropertyColorSet::Red: return "Red";
        case PropertyColorSet::Yellow: return "Yellow";
        case PropertyColorSet::Green: return "Green";
        case PropertyColorSet::DarkBlue: return "Dark Blue";
    }

    return "No color set";
}

Property::Property(const std::string &name, int price, PropertyColorSet color_set) : _name(name), _price(price),
    _color_set(color_set) {}

std::string Property::name() const { return _name; }
const char *Property::c_name() { return _name.c_str(); }
int Property::price() const { return _price; }
PropertyColorSet Property::color_set() const { return _color_set; }
