//
// Created by robert on 11/9/17.
//

#ifndef CPU_INSTRUCTIONS_RTM_H
#define CPU_INSTRUCTIONS_RTM_H
#include <immintrin.h>
#include <iostream>
#include "../include/tsx-cpuid.h"


bool transaction(int &a, int &b, int amount) {
    bool have_rtm = false;
    if (cpu_has_rtm())
        have_rtm = 1;
    else
        std::cout << "rtm not supported" << std::endl;
    if (have_rtm && _xbegin () == _XBEGIN_STARTED) {
        a += amount;
        b -= amount;
        _xend();
    } else {

    }

}

#endif //CPU_INSTRUCTIONS_RTM_H
