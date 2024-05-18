#include "stack_memory.h"
#include "functions.h"

StackMemory::StackMemory(const int &memory_size, const int &threading_size)
    : mem_size(memory_size), thread_size(threading_size) {
    memory_assertion(mem_size, thread_size);
    offset = mem_size / thread_size;
    stack_memory = (int*) malloc(memory_size * sizeof(int));
    if (stack_memory == NULL) {
        throw std::bad_alloc();
    } else {
        std::cout << "Memory is allocated" << std::endl;
    }
    this->print_stack_info();
    this->initialize_stack_memory();
    this->print_memory_values();
}

StackMemory::~StackMemory() {
    free(stack_memory);
    std::cout << "Stack memory is deallocated" << std::endl;
}

int* StackMemory::get_stack_memory() {
    return stack_memory;
}

void StackMemory::print_stack_info() {
    std::cout << "Full memory of thread is :" << this->mem_size * sizeof(int) << " bytes\n";
    std::cout << "Thread size is  :" << this->thread_size << "\n";
    std::cout << "Offset for memory direction is :" << this->offset  << "\n";
}

void StackMemory::print_memory_values() {
    for (int idx = 0; idx < this->mem_size; idx++) {
        std::cout << "Value : " << stack_memory[idx] << " is located at " << idx << " sequence of memory" << std::endl;
    }
}

void StackMemory::initialize_stack_memory() {
    int value = 0;
    for (int idx = 0; idx < this->mem_size; idx++) {
        stack_memory[idx] = value;
        value++;
    }
}
