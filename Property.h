//
// Created by busby08 on 16/06/25.
//

#ifndef PROPERTY_H
#define PROPERTY_H
#include <string>

enum class PropertyColorSet { Brown, LightBlue, Purple, Orange, Red, Yellow, Green, DarkBlue };

class Property {
private:
    const std::string _name;
    const int _price;
    const PropertyColorSet _color_set;

public:
    Property(const std::string &name, int price, PropertyColorSet color_set);

    std::string name() const;

    const char *c_name();
    int price() const;
    PropertyColorSet color_set() const;
};



#endif //PROPERTY_H
