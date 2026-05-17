//
// Created by busby08 on 04/07/25.
//

#include "Logger.h"
#include <fstream>

void Logger::write(const std::string &message) {
    std::ofstream file(log_file);

    file << message << std::endl;
    file.close();
}

void Logger::error(const std::string &message) {
    const std::string full_message = "[ERROR] " + message;
    write(message);
    exit(-1);
}

void Logger::info(const std::string &message) {
    const std::string full_message = "[INFO] " + message;
    write(message);
}

void Logger::warning(const std::string &message) {
    const std::string full_message = "[WARNING] " + message;
    write(message);
}


