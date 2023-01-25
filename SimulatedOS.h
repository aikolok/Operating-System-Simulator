/******************************************************************
Title:        Home Project - Operating System Class
Student:      Alima Asanbaeva
Date:         December 4, 2022
Description:  The header file for SimulatedOS class
******************************************************************/

#include <vector>
#include <string>
#include "Process.h"
#include "CPU.h"
#include "Disk.h"
#include "RAM.h"

#ifndef SIMULATED_OS_H
#define SIMULATED_OS_H


class SimulatedOS {
    private:
        int numOfDisks_;
        int amountOfRAM_;
        int pageSize_;
        std::vector<Process> readyQueue_;
        int PID_;
        CPU CPU_;
        RAM RAM_;
        std::vector<Disk> disks_;
    public:
        // Parameterized Constructor
        SimulatedOS( int numberOfDisks, int amountOfRAM, int pageSize );
        void NewProcess( int priority );
        void Exit();
        void PrintCPU() const;
        void PrintReadyQueue() const;
        void PrintDisk( int diskNumber ) const;
        void PrintDiskQueue( int diskNumber ) const;
        void PrintRAM() const;
        void DiskReadRequested( int diskNumber, std::string fileName );
        void DiskJobCompleted( int diskNumber );
        void FetchFrom( unsigned int memoryAddress );
};
#endif // SIMULATED_OS_H