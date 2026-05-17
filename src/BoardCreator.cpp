//
// Created by busby08 on 29/07/25.
//

#include "BoardCreator.h"

#include <fmt/core.h>



std::string BoardCreator::MultiplyString(const std::string &input, int size) {
    std::string new_string;

    while (size--) {
        new_string += input;
    }

    return new_string;
}

std::string BoardCreator::CenterString(const std::string &input, int size) {
    const bool sizeIsEven = size % 2 == 0;
    const bool useFinalRight = !sizeIsEven;
    std::string new_string = input;
    while (new_string.length() < size) {
        new_string = " " + new_string;
        if (useFinalRight || new_string.length() < size - 1)
            new_string += " ";
    }

    return new_string;
}

BoardCreator::BoardCreator(): topLeftCorner(0), topRightCorner(0), bottomLeftCorner(0), bottomRightCorner(0) {

}

// std::string BoardCreator::GenerateBoard() {
//     std::string message;
//
//     message += fmt::format(TopLeftCornerTemplate(), CenterString("Free Parking", propertySize),
//         CenterString("$60", propertySize));
//
//     return message;
// }
