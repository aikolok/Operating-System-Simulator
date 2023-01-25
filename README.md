# Operating System Simulator
This project is a C++ library that has a SimulatedOS class which contains methods that simulate an operating system.

CPU scheduling is priority-based. Every process has a priority number. The higher is the number, the higher is priority. The process with higher priority uses the CPU. The scheduling is preemptive. It means that if a process with the higher priority arrives to the ready-queue while a lower-priority process uses the CPU, the lower-priority process is preempted (that is moved back to ready-queue) while the higher priority process immediately starts using the CPU. 

For memory management, this simulation uses paging. If the memory is full, the least recently used frame is removed from memory.

Disk management is “first-come-first-served”. In other words, all disk I/O-queues are real queues (FIFO).

## How to run the project

The `main.cpp` file is included for testing. You can edit the `main.cpp` file and try different simulation scenarios. 

To compile the project, please run the following compilation command:
`g++  -std=c++17  *.cpp  -o runme`
