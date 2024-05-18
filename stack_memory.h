#ifndef STACK_MEMORY_H
#define STACK_MEMORY_H

#include <iostream>
#include <stdexcept>

class StackMemory {
public:
    int mem_size;
    int thread_size;
    int offset;
    int *stack_memory;

    StackMemory(const int &memory_size, const int &threading_size);
    ~StackMemory();

    int* get_stack_memory();
    void print_stack_info();
    void print_memory_values();
    void initialize_stack_memory();
};

#endif // STACK_MEMORY_H
