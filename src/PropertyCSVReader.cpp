//
// Created by busby08 on 23/06/25.
//

#include "PropertyCSVReader.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "utilities.h"
#include "Property.h"

std::vector<std::string> PropertyCSVReader::split_to_values(const std::string &line) {
    return split_string(line, ',');
}

std::vector<PropertyStruct> PropertyCSVReader::read(const std::string& file_path) {
    std::ifstream f(file_path);
    std::vector<std::string> headers;

    std::string header_line;
    getline(f, header_line);

    int current_string_position = 0;
    std::string current_header;

    while (current_string_position < header_line.length()) {
        char current_char = header_line[current_string_position];
        current_string_position++;

        if (current_char == ',') {
            headers.push_back(current_header);
            current_header = "";
            continue;
        }
        current_header += current_char;
    }

    std::vector<PropertyStruct> all_properties;


    std::string line;
    while (std::getline(f, line)) {
        std::vector<std::string> values = split_to_values(line);

        PropertyStruct temp_struct;

        for (int i = 0; i < values.size(); i++) {
            if (i >= headers.size()) break;
            current_header = headers[i];

            std::string current_value = values[i];

            try {
                int current_value_as_int = stoi(current_value);
                temp_struct.set_value(current_header, current_value_as_int);
            } catch (std::invalid_argument &e) {
                temp_struct.set_value(current_header, current_value);
            }
        }

        all_properties.push_back(temp_struct);
    }

    return all_properties;

}
