//
// Created by robert on 11/9/17.
//

#ifndef CPU_INSTRUCTIONS_RTM_H
#define CPU_INSTRUCTIONS_RTM_H
#include <immintrin.h>
#include <iostream>
#include <unistd.h>
#include <queue>
#include "../include/tsx-cpuid.h"
#include "sync.h"

using namespace std;

static Lock lock;

static bool rtm_supported = cpu_has_rtm() > 0;

bool transaction(int &a, int &b, int amount) {
    if (! rtm_supported) {
//        std::cout << "rtm not supported" << std::endl;
        lock.acquire();
        a += amount;
        b -= amount;
        lock.release();
        return true;
    }

    unsigned status = _xbegin();
    if (status == _XBEGIN_STARTED) {
        a += amount;
        sleep(100);
        b -= amount;
        _xend();
        return true;
    } else {
//        switch (status) {
//            case _XABORT_CONFLICT:
//                std::cout << "_XABORT_CONFLICT" << std::endl;
//                break;
//            case _XABORT_CAPACITY:
//                std::cout << "_XABORT_CAPACITY" << std::endl;
//                break;
//            default:
//                std::cout << "DEFAULT!" << std::endl;
//                break;
//        }
        return false;
    }

}







#endif //CPU_INSTRUCTIONS_RTM_H
