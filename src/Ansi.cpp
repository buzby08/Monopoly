//
// Created by busby08 on 17/06/25.
//

#include "Ansi.h"

#include <format>
#include <iostream>
#include <vector>
#include <bits/error_constants.h>

#include "utilities.h"

std::string Ansi::rgb_bg(int red, int green, int blue) {
    if (red < 0 || red > 255) {
        throw std::invalid_argument("Red value must be between 0 and 255");
    }
    if (green < 0 || green > 255) {
        throw std::invalid_argument("Green value must be between 0 and 255");
    }
    if (blue < 0 || blue > 255) {
        throw std::invalid_argument("Blue value must be between 0 and 255");
    }

    const std::string result = std::format("\u001b[48;2;{};{};{}m", red, green, blue);
    return result;
}

std::string Ansi::get_fg_from_user(const std::string &message) {
    std::vector<std::string> foreground_colors = {
    "black", "red", "green", "yellow", "blue", "magenta",
    "cyan", "white"};

    std::cout << message << std::endl;

    for (int i = 0; i < foreground_colors.size(); i++) {
        std::cout << std::format("{}. {}", i+1, foreground_colors[i]) << std::endl;
    }

    const int chosen_color = get_int(">> ", 1, foreground_colors.size());

    switch (chosen_color) {
        case 1: return black_fg;
        case 2: return red_fg;
        case 3: return green_fg;
        case 4: return yellow_fg;
        case 5: return blue_fg;
        case 6: return magenta_fg;
        case 7: return cyan_fg;
        case 8: return white_fg;
        default: throw std::invalid_argument("Invalid color");
    }
}

std::string Ansi::string_to_fg_color(const std::string &color) {
    if (color == "black") return black_fg;
    if (color == "red") return red_fg;
    if (color == "green") return green_fg;
    if (color == "yellow") return yellow_fg;
    if (color == "blue") return blue_fg;
    if (color == "magenta") return magenta_fg;
    if (color == "cyan") return cyan_fg;
    if (color == "white") return white_fg;
    return "";
}

std::string Ansi::rgb_fg(int red, int green, int blue) {
    if (red < 0 || red > 255) {
        throw std::invalid_argument("Red value must be between 0 and 255");
    }
    if (green < 0 || green > 255) {
        throw std::invalid_argument("Green value must be between 0 and 255");
    }
    if (blue < 0 || blue > 255) {
        throw std::invalid_argument("Blue value must be between 0 and 255");
    }

    const std::string result = std::format("\u001b[38;2;{};{};{}m", red, green, blue);
    return result;
}


