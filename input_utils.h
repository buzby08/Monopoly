//
// Created by busby08 on 15/06/25.
//

#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H
#include <string>

enum class LimitType { Min, Max };

int get_int(const std::string& message, int minimum_value, int maximum_value, bool minimum_used, bool maximum_used);
int get_int(const std::string& message, int limit, LimitType limit_type);
int get_int(const std::string& message, int minimum_value, int maximum_value);

#endif //INPUT_UTILS_H