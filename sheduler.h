#ifndef SHEDULER_H
#define SHEDULER_H

#include <iostream>
#include <vector>
#include <functional>
#include <thread>
#include <random>
#include <optional>
#include <ctime>
#include <numeric>
#include "stack_memory.h"
#include "functions.h"

class Sheduler {
private:
    //std::mutex LocalMutex;
    int thread_count;
    int time_limit_msc;
    std::vector<FunctionPtr> sheduler_functions;
    StackMemory sheduler_stack;
    std::vector<int> random_time_sleep_vector;
    int global_sum_milliseconds;

public:
    Sheduler(const int &memory_size, const int &green_count, const int &time_limit);
    void push_functions_to_vector(FunctionPtr add_func);
    void add_all_func_to_sheduler();
    std::vector<int> generateRandomIntegers(int count, int minValue, int maxValue);
    void green_execution();
};

#endif // SHEDULER_H
