//
// Created by busby08 on 17/06/25.
//

#ifndef Ansi_H
#define Ansi_H
#include <string>


class Ansi {
    static const std::string reset;

    static const std::string bold;
    static const std::string italic;
    static const std::string underline;

    static const std::string black_fg;
    static const std::string red_fg;
    static const std::string green_fg;
    static const std::string yellow_fg;
    static const std::string blue_fg;
    static const std::string magenta_fg;
    static const std::string cyan_fg;
    static const std::string white_fg;

    static const std::string black_bg;
    static const std::string red_bg;
    static const std::string green_bg;
    static const std::string yellow_bg;
    static const std::string blue_bg;
    static const std::string magenta_bg;
    static const std::string cyan_bg;
    static const std::string white_bg;

    static const std::string rgb_fg(int red, int green, int blue);

    static const std::string rgb_bg(int red, int green, int blue);

};



#endif //Ansi_H
