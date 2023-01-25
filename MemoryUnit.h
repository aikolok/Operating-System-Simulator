/******************************************************************
Title:        Home Project - Operating System Class
Student:      Alima Asanbaeva
Date:         December 4, 2022
Description:  The header file for MemoryUnit class
******************************************************************/

#include "Process.h"
#include <string>

#ifndef MEMORY_UNIT_H
#define MEMORY_UNIT_H


class MemoryUnit {
    private:
        int pageNum_;
        int processPID_;
        int timeStamp_;
    public:
        // Default Constructor
        MemoryUnit();
        // Parameterized Constructor
        MemoryUnit( int pageNum, int processPID, int timeStamp );
        int getPageNum() const;
        int getProcessPID() const;
        int getTimeStamp() const;
        void setPageNum( int pageNumber );
        void setProcessPID( int PID );
        void setTimeStamp( int timeStamp );
};
#endif // MEMORY_UNIT_H