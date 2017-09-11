//
// Created by robert on 11/9/17.
//

#ifndef CPU_INSTRUCTIONS_TIMER_H
#define CPU_INSTRUCTIONS_TIMER_H

#include <stdint-gcc.h>

inline uint64_t ticks() {
    uint32_t lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

#define CLFLUSH(ADDR)  __asm__ __volatile__ ("clflush (%0)" :: "r" (ADDR))

#endif //CPU_INSTRUCTIONS_TIMER_H
