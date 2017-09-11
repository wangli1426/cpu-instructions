#include <iostream>
#include "library.h"
#include "rtm.h"
int main() {
    int a=10, b;
    uint64_t start, end;
    start = ticks();
    b = a;
    __sync_synchronize();
    __builtin_ia32_clflush(&b);
    ++b;
    __builtin_ia32_clflush(&b);
    __sync_synchronize();
    end = ticks();
//    std::cout << b << std::endl;
    std::cout << "CPU cycles to complete the add: " << end - start << std::endl;

    int user1 = 100, user2 = 200, amount = 10;
    transaction(user1, user2, amount);
    std::cout << user1 << std::endl;
}
