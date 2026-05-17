//
// Created by busby08 on 04/07/25.
//

#ifndef LOGGER_H
#define LOGGER_H
#include <string>


class Logger {
    static void write(const std::string &message);

public:
    inline static std::string log_file = "Monopoly.LOG";

    static void error(const std::string &message);
    static void info(const std::string &message);
    static void warning(const std::string &message);
};



#endif //LOGGER_H
