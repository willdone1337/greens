#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <thread>

typedef int(*FunctionPtr)(int&, int&);

int is_io_ready(int &sleep_time, int &time_limit);
void memory_assertion(const int &mem_size, const int &thread_size);

#endif // FUNCTIONS_H