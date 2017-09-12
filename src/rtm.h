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

static SpinLock lock;

#ifdef FORCE_SOFTWARE_TRANSACTION
static bool rtm_supported = false;
#else
static bool rtm_supported = cpu_has_rtm() > 0;
#endif

bool transaction(int &a, int &b, int amount) {
    if (! rtm_supported) {
        lock.acquire();
        a += amount;
        b -= amount;
        lock.release();
        return true;
    }

    unsigned status = _xbegin();
    if (status == _XBEGIN_STARTED) {
        a += amount;
        b -= amount;
        _xend();
        return true;
    } else {
        return false;
    }

}







#endif //CPU_INSTRUCTIONS_RTM_H
