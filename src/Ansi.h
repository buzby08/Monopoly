//
// Created by busby08 on 17/06/25.
//

#ifndef Ansi_H
#define Ansi_H
#include <string>


class Ansi {
public:
    inline static const std::string reset = "\033[0m";

    static const std::string bold;
    static const std::string italic;
    static const std::string underline;

    inline static const std::string black_fg = "\033[30m";
    inline static const std::string red_fg = "\033[31m";
    inline static const std::string green_fg = "\033[32m";
    inline static const std::string yellow_fg = "\033[33m";
    inline static const std::string blue_fg = "\033[34m";
    inline static const std::string magenta_fg = "\033[35m";
    inline static const std::string cyan_fg = "\033[36m";
    inline static const std::string white_fg = "\033[37m";

    inline static const std::string black_bg = "\033[40m";
    inline static const std::string red_bg = "\033[41m";
    inline static const std::string green_bg = "\033[42m";
    inline static const std::string yellow_bg = "\033[43m";
    inline static const std::string blue_bg = "\033[44m";
    inline static const std::string magenta_bg = "\033[45m";
    inline static const std::string cyan_bg = "\033[46m";
    inline static const std::string white_bg = "\033[47m";

    /**
     * Create an ansi terminal foreground color from rgb values
     * @param red The red value (0 to 255)
     * @param green The green value (0 to 255)
     * @param blue The blue value (0 to 255)
     * @return The string ansi code for the inputted rgb color
     */
    static std::string rgb_fg(int red, int green, int blue);

    /**
     * Create an ansi terminal background color from rgb values
     * @param red The red value (0 to 255)
     * @param green The green value (0 to 255)
     * @param blue The blue value (0 to 255)
     * @return The string ansi code for the inputted rgb color
     */
    static std::string rgb_bg(int red, int green, int blue);

    static std::string get_fg_from_user(const std::string &message);

    static std::string string_to_fg_color(const std::string &color);
};



#endif //Ansi_H
