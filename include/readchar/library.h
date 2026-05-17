#ifndef READCHAR_LIBRARY_H
#define READCHAR_LIBRARY_H

#include <string>
#include <vector>

#ifdef _WIN32
#include "win_readchar.h"
#else
#include "posix_readchar.h"
#endif

namespace readchar::keys {
    constexpr char LF = '\x0a';
    constexpr char CR = '\x0d';
    constexpr char SPACE = '\x20';
    constexpr char TAB = '\x09';
    constexpr char CTRL_A = '\x01';
    constexpr char CTRL_B = '\x02';
    constexpr char CTRL_C = '\x03';
    constexpr char CTRL_D = '\x04';
    constexpr char CTRL_E = '\x05';
    constexpr char CTRL_F = '\x06';
    constexpr char CTRL_G = '\x07';
    constexpr char CTRL_H = '\x08';
    constexpr char CTRL_I = TAB;
    constexpr char CTRL_J = LF;
    constexpr char CTRL_K = '\x0b';
    constexpr char CTRL_L = '\x0c';
    constexpr char CTRL_M = CR;
    constexpr char CTRL_N = '\x0e';
    constexpr char CTRL_O = '\x0f';
    constexpr char CTRL_P = '\x10';
    constexpr char CTRL_Q = '\x11';
    constexpr char CTRL_R = '\x12';
    constexpr char CTRL_S = '\x13';
    constexpr char CTRL_T = '\x14';
    constexpr char CTRL_U = '\x15';
    constexpr char CTRL_V = '\x16';
    constexpr char CTRL_W = '\x17';
    constexpr char CTRL_X = '\x18';
    constexpr char CTRL_Y = '\x19';
    constexpr char CTRL_Z = '\x1a';
    constexpr char ESCAPE = '\x1b';

#ifdef _win32
#else
    const std::string ARR_UP = "\x1b\x5b\x41";
    const std::string ARR_DOWN = "\x1b\x5b\x42";
    const std::string ARR_LEFT = "\x1b\x5b\x43";
    const std::string ARR_RIGHT = "\x1b\x5b\x44";
#endif

}

namespace readchar::exceptions {
    class KeyboardInterrupt final : public std::exception {
        public:
            [[nodiscard]] const char* what() const noexcept override {
                return "KeyboardInterrupt: Ctrl+C pressed.";
            }
        };

    class MissingCharacter final : public std::exception {
    public:
        [[nodiscard]] const char* what() const noexcept override {
            return "MissingCharacter: A character was missing in a non-blocking call";
        }
    };

    class NonBlocking final : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "NonBlocking: Cannot reverse non-blocking properties because they were never set";
        }
    };
}

namespace readchar {
    inline const std::vector INTERRUPT_KEYS = {keys::CTRL_C};

    inline int readcharNonBlocking() {
        #ifdef _WIN32
                return win_readchar::readcharNonBlocking();
        #else
                return posix_readchar::readcharNonBlocking();
        #endif
    }

    inline char readchar() {
        #ifdef _WIN32
                return win_readchar::readchar();
        #else
                return posix_readchar::readchar();
        #endif
    }

    inline std::string readkeyNonBlocking() {
        #ifdef _WIN32
                return win_readchar::readkeyNonBlocking();
        #else
                return posix_readchar::readkeyNonBlocking();
        #endif
    }

    inline std::string readkey() {
        #ifdef _WIN32
            return win_readchar::readkey();
        #else
            return posix_readchar::readkey();
        #endif
    }
}


#endif //READCHAR_LIBRARY_H