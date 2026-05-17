//
// Created by busby08 on 16/06/25.
//

#include "Property.h"

#include <format>
#include <string>
#include <system_error>

#include "Ansi.h"
#include "UserPlayer.h"


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
        case PropertyColorSet::Invalid: return "Invalid";
    }

    return "No color set";
}


Property::Property(const std::string &name, int cost, int space, int site, int one_house, int two_house, int three_house,
    int four_house, int hotel, PropertyColorSet color_set) {
    _name = name;
    _cost = cost;
    _space = space;
    _mortgage = cost / 2;
    _base_rent = site;
    _rent_one_house = one_house;
    _rent_two_houses = two_house;
    _rent_three_houses = three_house;
    _rent_four_houses = four_house;
    _rent_hotel = hotel;
    _color_set = color_set;
}

Property::Property(const PropertyStruct& data) {
    _name = data.name;
    _mortgage = data.mortgage;
    _base_rent = data.base_rent;
    _color_set = data.colour_group;
    _cost = data.cost;
    _space = data.space;

    _rent_one_house = data.rent_1;
    _rent_two_houses = data.rent_2;
    _rent_three_houses = data.rent_3;
    _rent_four_houses = data.rent_4;
    _rent_hotel = data.hotel_rent;
}

Property::Property()
{
}


std::string Property::name() const { return _name; }
const char *Property::c_name() { return _name.c_str(); }
int Property::cost() const { return _cost; }
PropertyColorSet Property::color_set() const { return _color_set; }

int Property::rent() const {
    if (_has_a_hotel) return _rent_hotel;

    switch (_number_of_houses) {
        case 0: return _base_rent;
        case 1: return _rent_one_house;
        case 2: return _rent_two_houses;
        case 3: return _rent_three_houses;
        case 4: return _rent_four_houses;
        default:
            throw std::logic_error("Invariant violated: _number_of_houses value out of bounds (expected 0-4)");
    }
}

int Property::space() const { return _space; }

bool Property::owned() const {
    return _owned;
}

Player* Property::owner() const {
    return _owner;
}

int Property::owner_id() const
{
    return _owner_id;
}

void Property::addHouse(const int number_of_houses) {
    _number_of_houses = number_of_houses;
    if (number_of_houses > 4) _number_of_houses = 4;
    if (number_of_houses < 0) _number_of_houses = 0;
}

std::string Property::output() {
    std::string message;

    message += std::format("{},", _name);
    message += std::format("{},", _space);
    message += std::format("{},", _cost);
    message += std::format("{},", _mortgage);
    message += std::format("{},", _base_rent);
    message += std::format("{},", _rent_one_house);
    message += std::format("{},", _rent_two_houses);
    message += std::format("{},", _rent_three_houses);
    message += std::format("{},", _rent_four_houses);
    message += std::format("{}", _rent_hotel);

    return message;
}

void Property::set_owner(Player* new_owner) {
    _owned = true;

    _owner = new_owner;

    _owner_id = new_owner->Id();
}

string Property::get_name_and_color_string(std::string previousColour) const
{
    std::string color;

    switch (_color_set)
    {
    case PropertyColorSet::Brown:
        color = Ansi::rgb_fg(149, 84, 54);
        break;
    case PropertyColorSet::LightBlue:
        color = Ansi::rgb_fg(170, 224, 250);
        break;
    case PropertyColorSet::Pink:
        color = Ansi::rgb_fg(217, 58, 150);
        break;
    case PropertyColorSet::Orange:
        color = Ansi::rgb_fg(247, 148, 29);
        break;
    case PropertyColorSet::Red:
        color = Ansi::rgb_fg(237, 28, 36);
        break;
    case PropertyColorSet::Yellow:
        color = Ansi::rgb_fg(255, 242, 0);
        break;
    case PropertyColorSet::Green:
        color = Ansi::rgb_fg(31, 178, 90);
        break;
    case PropertyColorSet::DarkBlue:
        color = Ansi::rgb_fg(0, 114, 188);
        break;
    case PropertyColorSet::Invalid:
        color = Ansi::reset;
        break;
    }

    const string message = std::format("{}{} ({}){}", color, _name, colorSetToString(_color_set), previousColour);
    return message;
}

bool Property::operator==(std::vector<Property>::const_reference property) const {
    return (_name == property._name) && (_cost == property._cost) && (_color_set == property._color_set);
}
