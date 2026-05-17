//
// Created by busby08 on 23/06/25.
//

#ifndef PROPERTYCSVREADER_H
#define PROPERTYCSVREADER_H
#include <string>
#include <vector>

#include "Property.h"


class PropertyCSVReader {
    static std::vector<std::string> split_to_values(const std::string& line);
public:
    static std::vector<PropertyStruct> read(const std::string& file_path);
};



#endif //PROPERTYCSVREADER_H
