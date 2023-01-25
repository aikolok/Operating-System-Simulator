/******************************************************************
Title:        Home Project - Operating System Class
Student:      Alima Asanbaeva
Date:         December 4, 2022
Description:  The header file for Disk class
******************************************************************/

#include "Process.h"
#include <string>
#include <deque>

#ifndef DISK_H
#define DISK_H


class Disk {
    private:
        int diskNumber_;
        Process servingProcess_;
        std::string servingFileName_;
        std::deque<std::string> fileQueue_;
        std::deque<Process> diskQueue_;
    public:
        // Parameterized Constructor
        Disk( int diskNumber );
        int getDiskNumber() const;
        void printDisk() const;
        void printDiskQueue() const;
        void addToDiskQueue( Process requesting_process, std::string fileName );
        Process completeJob();
};
#endif // DISK_H