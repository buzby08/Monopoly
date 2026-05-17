//
// Created by busby08 on 11/07/25.
//

#ifndef POSIX_READCHAR_H
#define POSIX_READCHAR_H

#ifndef _WIN32

#include <string>
#include <vector>

namespace posix_readchar {
    class posix_readchar_helper {
        inline static int old_flags = -1;

    public:
        static void set_nonblocking(int fd, bool enable);
    };

    int readcharNonBlocking();

    char readchar();

    std::string readkeyNonBlocking();

    std::string readkey();
}

#endif //_WIN32 ELSE

#endif //POSIX_READCHAR_H
