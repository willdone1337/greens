# Green Threads Scheduler

This project implements a high-level abstraction of working green threads in C++. It provides a scheduling mechanism for managing green threads, allowing for efficient concurrent execution within a single process and currently support only single thread.

## Overview

Green threads, also known as user-level threads or fibers, are lightweight threads managed entirely by the runtime or a user-space threading library rather than the operating system kernel. They provide a way to perform concurrent I/O execution within a single process context.

This project aims to demonstrate a simple implementation of green threads and a scheduling mechanism to manage their execution. It includes components such as a stack memory allocator, a scheduler, and functions for task execution.

## Features

- Lightweight green thread implementation
- Cooperative multitasking scheduler
- Stack memory allocation for green threads
- Example functions for task execution (e.g., I/O readiness)

## Usage

To build the project, simply compile the source files using a CMake:

```bash
mkdir build && cd build && cmake .. && make && ./main
