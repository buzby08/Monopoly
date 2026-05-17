//
// Created by busby08 on 11/07/25.
//

#ifndef WIN_READCHAR_H
#define WIN_READCHAR_H

#ifdef _WIN32

#include <string>
#include <vector>
#include <conio.h>
#include <cstdint>

namespace win_readchar {
    int readcharNonBlocking();

    char readchar();

    std::string readkeyNonBlocking();

    std::string readkey();

    uint32_t get_codepoint(const std::string &utf8_input);

    std::string normalise_utf8(const std::string &utf8_input);
}

#endif //_WIN32

#endif //WIN_READCHAR_H
