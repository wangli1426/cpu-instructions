#include <iostream>
#include "library.h"
#include "rtm.h"
#include "worker.h"
int main() {
    if (rtm_supported) {
        std::cout << "transactions are being executed using rtm!" << std::endl;
    } else {
        std::cout << "transactions are being executed using software locks" << std::endl;
    }
    const int number_of_transactions = 10000000;
    transaction_context context(1000, 1000);

    int *transactions = new int[number_of_transactions];

    const int number_of_threads = 4;
    pthread_t tid[number_of_threads];

    int sum = 0;
    for (int i = 0; i < number_of_transactions - 1; ++i) {
        int transaction = rand() % 100 - 50;
        transactions[i] = transaction;
        sum += transaction;
    }
    transactions[number_of_transactions - 1] = - sum;

    sum = 0;
    for (int i = 0; i < number_of_transactions; ++i) {
        sum += transactions[i];
    }

    for (int i = 0; i < number_of_transactions; ++i) {
        context.queues.push(transactions[i]);
    }

    uint64_t start = ticks();
    for (int i = 0; i < number_of_threads; ++i) {
        pthread_create(&tid[i], NULL, worker, &context);
    }

    for (int i = 0; i < number_of_threads; ++i) {
        pthread_join(tid[i], NULL);
    }

    uint64_t end = ticks();
    std::cout << number_of_transactions << " transactions executed." << std::endl;
    if (context.account_a == 1000 && context.account_b == 1000) {
        std::cout << "all transactions are atomic" << std::endl;
    } else {
        std::cout << "inconsistent results!" << std::endl;
        std::cout << "a: " + context.account_a << " b: " << context.account_b << std::endl;
    }

    std::cout << "=================================" << std::endl;

    std::cout << "thread: " << number_of_threads << ", cpu cycles per transaction: "
              << (end - start) / number_of_transactions << std::endl;
    delete[] transactions;
}
