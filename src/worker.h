//
// Created by robert on 12/9/17.
//

#ifndef CPU_INSTRUCTIONS_WORKER_H
#define CPU_INSTRUCTIONS_WORKER_H
#include "sync.h"
namespace rtm {
    struct transaction_context {
        alignas(64) int account_a;
        alignas(64) int account_b;
        Lock lock;
        queue<int> queues;
        volatile bool terminate_flag;

        transaction_context(int a, int b) : account_a(a), account_b(b), terminate_flag(false) {};
    };


    void *worker(void *args) {
        transaction_context *context = reinterpret_cast<transaction_context *>(args);
        int volume;
        bool executed;
        int retried = 0;
        while (true) {
            context->lock.acquire();
            int size = context->queues.size();
            if (size == 0) {
                context->lock.release();
                break;
            }

            volume = context->queues.front();
            context->queues.pop();
            context->lock.release();

            executed = false;
            while (!executed) {
                executed = transaction(context->account_a, context->account_b, volume);
                retried += !executed;
            }
        }
        lock.acquire();
        std::cout << "thread " << pthread_self() << ": " << retried << " retries." << std::endl;
        lock.release();

    }
}

#endif //CPU_INSTRUCTIONS_WORKER_H
