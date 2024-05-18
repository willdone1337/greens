#include "functions.h"

int is_io_ready(int &sleep_time, int &time_limit) {
    int partitioning_value_of_time = 10;
    std::this_thread::sleep_for(std::chrono::milliseconds(time_limit));
    return sleep_time <= time_limit;
};

void memory_assertion(const int &mem_size, const int &thread_size) {
    if (mem_size == 0) {
        throw std::invalid_argument("Memory is set as 0 bytes!");
    };

    if (thread_size == 0) {
        throw std::invalid_argument("Number of threads are not set!");
    };

    if (mem_size < thread_size) {
        std::cout << mem_size << " " << thread_size << std::endl;
        throw std::invalid_argument("Stack memory have to set minimum 1 unit per thread!");
    };

    if ((mem_size % thread_size) != 0) {
        throw std::invalid_argument("Memory size must be divisible to thread size!");
    };
};
