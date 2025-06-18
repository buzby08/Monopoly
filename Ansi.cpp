//
// Created by busby08 on 17/06/25.
//

#include "Ansi.h"

#include <format>
#include <bits/error_constants.h>

const std::string Ansi::rgb_bg(int red, int green, int blue) {
    if (red < 0 || red > 255) {
        throw std::errc::invalid_argument;
    }
    if (green < 0 || green > 255) {
        throw std::errc::invalid_argument;
    }
    if (blue < 0 || blue > 255) {
        throw std::errc::invalid_argument;
    }

    const std::string result = std::format("\u001b[48;2;{};{};{}m", red, green, blue);
    return result;
}

const std::string Ansi::rgb_fg(int red, int green, int blue) {
    if (red < 0 || red > 255) {
        throw std::errc::invalid_argument;
    }
    if (green < 0 || green > 255) {
        throw std::errc::invalid_argument;
    }
    if (blue < 0 || blue > 255) {
        throw std::errc::invalid_argument;
    }

    const std::string result = std::format("\u001b[38;2;{};{};{}m", red, green, blue);
    return result;
}
