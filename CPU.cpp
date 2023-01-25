/******************************************************************
Title:        Home Project - Operating System Class
Student:      Alima Asanbaeva
Date:         December 4, 2022
Description:  The implementation file for CPU class
******************************************************************/

#include "CPU.h"
#include <iostream>


/**
 * Default Constructor
*/
CPU::CPU() 
{
    runningProcess_ = Process();
}


/**
 * @param readyQueue - Ready-Queue of the CPU
 * CPU gets the process with the highest PID
 * following the preemptive principle.
*/
void CPU::updateCPU( std::vector<Process>& readyQueue )
{
    int max_priority = runningProcess_.getPriority();
    if (readyQueue.size() > 0) {
        for (int i = 0; i < readyQueue.size(); ++i)
        {
            if (readyQueue[i].getPriority() > max_priority) {
                max_priority = readyQueue[i].getPriority();
                Process leaving_cpu_process = runningProcess_;
                runningProcess_ = readyQueue[i];
                readyQueue.erase(readyQueue.begin() + i);
                if (leaving_cpu_process.getPriority() != -1) {
                    readyQueue.push_back(leaving_cpu_process);
                }
            }
        }
    }
}


/**
 * @param readyQueue - Ready-Queue of the CPU
 * @return terminated process
 * Currently running process leaves the CPU.
*/
Process CPU::terminate_process( std::vector<Process>& readyQueue )
{
    Process terminatedProcess = runningProcess_;
    if (readyQueue.size() > 0) {
        runningProcess_ = readyQueue[0];
        readyQueue.erase(readyQueue.begin() + 0);
        updateCPU(readyQueue);
    } else {
        runningProcess_ = Process();
    }
    return terminatedProcess;
}


/**
 * @return the PID of the currently running process.
*/
int CPU::print() const
{
    return runningProcess_.getPID();
}


/**
 * @param readyQueue - Ready-Queue of the CPU
 * @return process that requested disk read
 * Currently running process that requested 
 * disk read leaves the CPU.
*/
Process CPU::diskRequest( std::vector<Process>& readyQueue )
{
    if (runningProcess_.getPID() != -1) 
    {
        Process leaving_process = runningProcess_;
        terminate_process(readyQueue);
        return leaving_process;
    }
    return Process();
}


/**
 * @return currently running process in the CPU.
*/
Process CPU::getCurrentProcess() const
{
    return runningProcess_;
}


/**
 * @param currentProcess - currently running process in the CPU
 * Updates currently running process in the CPU with it's
 * most recent program counter and page number.
*/
void CPU::updateProcess( Process currentProcess )
{
    runningProcess_.setPageNum(currentProcess.getPageNum());
    runningProcess_.setProgramCounter(currentProcess.getProgramCounter());
}