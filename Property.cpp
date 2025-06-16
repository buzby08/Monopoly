//
// Created by busby08 on 16/06/25.
//

#include "Property.h"
#include <string>

using namespace std;

Property::Property(const std::string &name, int price, PropertyColorSet color_set) : _name(name), _price(price),
    _color_set(color_set) {}

std::string Property::name() const { return _name; }
const char *Property::c_name() { return _name.c_str(); }
int Property::price() const { return _price; }
PropertyColorSet Property::color_set() const { return _color_set; }
