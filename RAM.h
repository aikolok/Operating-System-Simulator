/******************************************************************
Title:        Home Project - Operating System Class
Student:      Alima Asanbaeva
Date:         December 4, 2022
Description:  The header file for RAM class
******************************************************************/

#include "Process.h"
#include "MemoryUnit.h"
#include <string>
#include <vector>

#ifndef RAM_H
#define RAM_H


class RAM {
    private:
        int numOfFrames_;
        std::vector<MemoryUnit> RAMmemory_;
        int timeStampCounter_;
        int numOfProcessesInMem_;
    public:
        // Default Constructor
        RAM();
        void setSize( int numOfFrames );
        void print() const;
        void addNewProcess( Process new_process, Process currentProcess );
        void updateTimeStamp( Process currentProcess );
        void updateMemory( Process new_process );
        void remove_process( Process terminatedProcess );
        void updateProcess( Process currentProcess );
};
#endif // RAM_H