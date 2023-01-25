/******************************************************************
Title:        Home Project - Operating System Class
Student:      Alima Asanbaeva
Date:         December 4, 2022
Description:  The implementation file for SimulatedOS class
******************************************************************/

#include "SimulatedOS.h"
#include <iostream>


/**
 * Parameterized Constructor
 * @param numberOfDisks: number of hard disks in the simulated computer
 * @param amountOfRAM: amount of memory
 * @param pageSize: page size
 * Updates member variables with given parameters.
 * Disks and pages enumeration starts from 0.
 * Throws an exception if the amount of RAM isn't 
 * divisible by page size.
 */
SimulatedOS::SimulatedOS( int numberOfDisks, int amountOfRAM, int pageSize ) : numOfDisks_(numberOfDisks), amountOfRAM_(amountOfRAM), pageSize_(pageSize)
{
    // The amountOfRAM should always be divisible by pageSize.
    if (amountOfRAM_ % pageSize_ != 0) {
        throw std::invalid_argument("\n\n--- The amount of RAM should be divisible by Page Size ---\n");
    }
    PID_ = 1;
    for (int i = 0; i < numOfDisks_; ++i) 
    {
        disks_.push_back(Disk( i ));
    }
    RAM_.setSize( amountOfRAM_ / pageSize_ );
} 


/**
 * @param priority: the priority number of the process
 * Creates new process with given priority in the system,
 * records it in the RAM and pushes it either into the 
 * Ready-Queue or the CPU starts executing it right away
 * depending on the new process's priority number.
 */
void SimulatedOS::NewProcess( int priority )
{
    Process new_process{priority, PID_};
    readyQueue_.push_back(new_process);
    PID_++;
    CPU_.updateCPU(readyQueue_);
    RAM_.addNewProcess(new_process, CPU_.getCurrentProcess());
}


/**
 * Terminates the currently running process in the CPU.
 * Frees all the memory resources used by this process.
 */
void SimulatedOS::Exit()
{
    Process terminatedProcess = CPU_.terminate_process(readyQueue_);
    RAM_.remove_process(terminatedProcess);
    Process currentProcess = CPU_.getCurrentProcess();
    if (currentProcess.getPID() != -1) {
        RAM_.updateTimeStamp(currentProcess);
    }
}


/**
 * Prints out the currently running process in the CPU.
 * If the CPU is not running any process, it prints out
 * that it is idle. 
 */
void SimulatedOS::PrintCPU() const
{
    if ( CPU_.print() == -1 ) {
        std::cout << "CPU is idle." << std::endl << std::endl;
    } else {
        std::cout << "CPU: " << CPU_.print() << "." << std::endl << std::endl;
    }   
}


/**
 * Prints out the PIDs of processes in the Ready-Queue in any order.
*/
void SimulatedOS::PrintReadyQueue() const
{
    if (readyQueue_.size() == 0) {
        std::cout << "Ready-Queue is empty." << std::endl << std::endl;
    } else {
        std::cout << "Ready-Queue:";
        for (int i = 0; i < readyQueue_.size(); ++i)
        {
            std::cout << " " << readyQueue_[i].getPID();
        }
        std::cout << std::endl << std::endl;
    }
}


/**
 * @param diskNumber: disk number
 * Prints the PID of the process served by the specified 
 * disk number and the name of the file served for that process.
*/
void SimulatedOS::PrintDisk( int diskNumber ) const 
{
    if (diskNumber == numOfDisks_ || diskNumber > numOfDisks_ || diskNumber < 0) {
        std::cout << "Instruction ignored: no disk with such number exists." << std::endl << std::endl;
    } else {
        for (int i = 0; i < disks_.size(); ++i)
        {
            if (disks_[i].getDiskNumber() == diskNumber)
            {
                disks_[i].printDisk();
            }
        }
    }
}


/**
 * @param diskNumber: disk number
 * Prints PIDs of the processes in the I/O-queue of the 
 * specified disk number starting from the 
 * “next to be served” process.
*/
void SimulatedOS::PrintDiskQueue( int diskNumber ) const
{
    if (diskNumber == numOfDisks_ || diskNumber > numOfDisks_ || diskNumber < 0) {
        std::cout << "Instruction ignored: no disk with such number exists." << std::endl << std::endl;
    } else {
        for (int i = 0; i < disks_.size(); ++i)
        {
            if (disks_[i].getDiskNumber() == diskNumber)
            {
                disks_[i].printDiskQueue();
            }
        }
    }
}


/**
 * @param diskNumber: disk number
 * @param fileName: file name
 * Currently running process requests to read the specified file 
 * from the disk with a given number.
*/
void SimulatedOS::DiskReadRequested( int diskNumber, std::string fileName )
{
    if (diskNumber == numOfDisks_ || diskNumber > numOfDisks_ || diskNumber < 0) {
        std::cout << "Instruction ignored: no disk with such number exists." << std::endl << std::endl;
    } else {
        for (int i = 0; i < disks_.size(); ++i)
        {
            if (disks_[i].getDiskNumber() == diskNumber)
            {
                Process requesting_process = CPU_.diskRequest(readyQueue_); 
                Process current_process = CPU_.getCurrentProcess();
                if (current_process.getPID() != -1) {
                    RAM_.updateProcess(current_process);
                }
                if (requesting_process.getPID() != -1) {
                    disks_[i].addToDiskQueue( requesting_process, fileName );
                } else {
                    std::cout << "Instruction ignored. CPU is idle." << std::endl << std::endl;
                }
            }
        }
    }
}


/**
 * @param diskNumber: disk number
 * A disk with a specified number completes currently 
 * serving single job.
*/
void SimulatedOS::DiskJobCompleted( int diskNumber )
{
    if (diskNumber == numOfDisks_ || diskNumber > numOfDisks_ || diskNumber < 0) {
        std::cout << "Instruction ignored: no disk with such number exists." << std::endl << std::endl;
    } else {
        for (int i = 0; i < disks_.size(); ++i)
        {
            if (disks_[i].getDiskNumber() == diskNumber)
            {
                Process completed_process = disks_[i].completeJob();
                if (completed_process.getPID() != -1) {
                    readyQueue_.push_back(completed_process);
                    CPU_.updateCPU(readyQueue_);
                    Process current_process = CPU_.getCurrentProcess();
                    if (current_process.getPID() == completed_process.getPID()) {
                        RAM_.updateProcess(current_process);
                    }
                } else {
                    std::cout << "Instruction ignored. The disk " << disks_[i].getDiskNumber() << " is idle." << std::endl;
                }
            }
        }
    }
}


/**
 * Prints a sorted list of all frames in the system, 
 * corresponding page numbers stored in it, and 
 * PIDs of the processes that own those pages.
*/
void SimulatedOS::PrintRAM() const
{
    RAM_.print();
}


/**
 * @param memoryAddress: memory address
 * Fetches instruction from RAM at the specified logical address
 * for the currently running process in the CPU.
*/
void SimulatedOS::FetchFrom( unsigned int memoryAddress )
{
    int pageNum = memoryAddress / pageSize_;
    Process currentProcess = CPU_.getCurrentProcess();
    if (currentProcess.getPID() != -1) {
        currentProcess.setPageNum(pageNum);
        currentProcess.setProgramCounter(memoryAddress);
        CPU_.updateProcess(currentProcess);
        RAM_.updateProcess(currentProcess);
    } else {
        std::cout << "This instruction is ignored. CPU is idle."
        << std::endl << std::endl;
    }
}