#include "sheduler.h"

Sheduler::Sheduler(const int &memory_size, const int &green_count, const int &time_limit)
    : thread_count(green_count), time_limit_msc(time_limit), sheduler_stack(memory_size, green_count) {
    this->add_all_func_to_sheduler();
    random_time_sleep_vector = generateRandomIntegers(this->sheduler_stack.mem_size, 300, 500);
    global_sum_milliseconds = std::accumulate(random_time_sleep_vector.begin(), random_time_sleep_vector.end(), 0);
    for (const auto &x: random_time_sleep_vector) {
        std::cout << x << " time \n";
    };
};

void Sheduler::push_functions_to_vector(FunctionPtr add_func) {
    sheduler_functions.push_back(add_func);
};

void Sheduler::add_all_func_to_sheduler() {
    for (int i = 0; i < this->sheduler_stack.mem_size; i++) {
        push_functions_to_vector(is_io_ready);
    };
};

std::vector<int> Sheduler::generateRandomIntegers(int count, int minValue, int maxValue) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minValue, maxValue);

    std::vector<int> random_integers;
    random_integers.reserve(count);

    for (int i = 0; i < count; ++i) {
        random_integers.push_back(dis(gen));
    };

    return random_integers;
};

void Sheduler::green_execution() {
    int mem_pos_used = 0;
    int mem_index = 0;
    int current_thread_position = 0;
    int current_thread = 0;
    int sleep_time;
    std::vector<bool> time_out_exceed_function_idx(this->sheduler_stack.mem_size, false);
    std::chrono::steady_clock::time_point default_time_point;
    std::vector<std::chrono::steady_clock::time_point> function_input_timing(this->sheduler_stack.mem_size);
    std::vector<std::chrono::steady_clock::time_point> exceed_functions_last_delay(this->sheduler_stack.mem_size);
    auto global_start = std::chrono::steady_clock::now();

    while (mem_pos_used < this->sheduler_stack.mem_size) {
        for (int current_offset = 0; current_offset < this->sheduler_stack.offset; current_offset++) {
            for (int current_thread = 0; current_thread < this->sheduler_stack.thread_size; current_thread++) {
                mem_index = (current_thread * this->sheduler_stack.offset) + current_offset;
                if (time_out_exceed_function_idx[mem_index] == true) {
                    continue;
                }
                int current_stack_value = this->sheduler_stack.stack_memory[mem_index];

                auto current_time = std::chrono::steady_clock::now();
                if (exceed_functions_last_delay[mem_index] == default_time_point) {
                    sleep_time = this->random_time_sleep_vector[mem_index];
                } else {
                    std::chrono::duration<double, std::milli> delay_from_last_execution = current_time - function_input_timing[mem_index];
                    this->random_time_sleep_vector[mem_index] -= static_cast<int>(delay_from_last_execution.count());
                    sleep_time = std::max(1, this->random_time_sleep_vector[mem_index]);
                };

                function_input_timing[mem_index] = current_time;

                bool result = this->sheduler_functions[mem_index](sleep_time, time_limit_msc);
                auto time_after_execution = std::chrono::steady_clock::now();
                if (result == true) {
                    time_out_exceed_function_idx[mem_index] = true;
                    this->sheduler_stack.stack_memory[mem_index] = 42; //just assign to stack some var
                    mem_pos_used++;
                } else {
                    time_out_exceed_function_idx[mem_index] = false;
                    exceed_functions_last_delay[mem_index] = time_after_execution;
                };
            };
        };
    };
    auto global_end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> global_execution = global_end - global_start;
    std::cout << "Whole time consumption is " << global_execution.count() << std::endl;
    std::cout << "Without asynch it will took " << global_sum_milliseconds << std::endl;
};
