//
// Created by busby08 on 29/06/25.
//

#ifndef RANDOM_H
#define RANDOM_H

#include <random>



class Random {
    inline static std::random_device random_device;
    inline static std::mt19937 mersenne_twister_engine{random_device()};

public:
    static int getRandomInt(const int min, const int max) {
        std::uniform_int_distribution<> random{min, max};
        return random(mersenne_twister_engine);
    }
};



#endif //RANDOM_H
