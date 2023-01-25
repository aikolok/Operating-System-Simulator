/******************************************************************
Title:        Home Project - Operating System Class
Student:      Alima Asanbaeva
Date:         December 4, 2022
Description:  The header file for CPU class
******************************************************************/

#include "Process.h"
#include <vector>

#ifndef CPU_H
#define CPU_H


class CPU {
    private:
        Process runningProcess_;
    public:
        // Default Constructor
        CPU();
        void updateCPU( std::vector<Process>& readyQueue );
        int print() const;
        Process getCurrentProcess() const;
        Process terminate_process( std::vector<Process>& readyQueue );
        Process diskRequest( std::vector<Process>& readyQueue );
        void updateProcess( Process currentProcess );
};
#endif // CPU_H