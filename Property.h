//
// Created by busby08 on 16/06/25.
//

#ifndef PROPERTY_H
#define PROPERTY_H
#include <string>

enum class PropertyColorSet { Brown, LightBlue, Pink, Orange, Red, Yellow, Green, DarkBlue };

std::string colorSetToString(PropertyColorSet colorSet);

class Property {
private:
    std::string _name;
    int _price;
    PropertyColorSet _color_set;

public:
    Property(const std::string &name, int price, PropertyColorSet color_set);

    std::string name() const;

    const char *c_name();
    int price() const;
    PropertyColorSet color_set() const;
};



#endif //PROPERTY_H
