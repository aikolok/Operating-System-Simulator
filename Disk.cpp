/******************************************************************
Title:        Home Project - Operating System Class
Student:      Alima Asanbaeva
Date:         December 4, 2022
Description:  The implementation file for Disk class
******************************************************************/

#include "Disk.h"
#include <iostream>


/**
 * Parameterized Constructor
 * @param diskNumber: number of the hard disk
 * Disk enumeration starts from 0.
 */
Disk::Disk( int diskNumber ) : diskNumber_(diskNumber)
{
    servingProcess_ = Process();
    servingFileName_ = "";
}


/**
 * @return Disk number
 * Disk enumeration starts from 0.
 */
int Disk::getDiskNumber() const
{
    return diskNumber_;
}


/**
 * Prints out the current process that disk is serving.
 * If there is no process being served, 
 * prints out that disk is idle.
 */
void Disk::printDisk() const
{
    if (servingProcess_.getPID() == -1) {
        std::cout << "Disk " << diskNumber_ << " is idle." << std::endl << std::endl;
    } else {
        std::cout << "Disk " << diskNumber_ << ":" << std::endl
                  << "PID: " << servingProcess_.getPID() << std::endl
                  << "File: " << servingFileName_ 
                  << std::endl << std::endl;
    }
}


/**
 * Prints out the I/O-queue of the disk (PIDs of the processes 
 * and their corresponding requested file names).
 * If there are no processes in the I/O-queue, 
 * then prints out that the I/O-queue is empty.
 */
void Disk::printDiskQueue() const
{
    if (diskQueue_.size() == 0) {
        std::cout << "I/O-queue of disk " << diskNumber_ 
                  << " is empty." << std::endl << std::endl;
    } else {
        std::cout << "I/O-queue of disk " 
                  << diskNumber_ << ":";
        for (int i = 0; i < diskQueue_.size(); ++i) 
        {
            std::cout << " " << diskQueue_[i].getPID();
        }
        std::cout << std::endl << std::endl;
    }
}


/**
 * @param requesting_process: process that needs to use the disk
 * @param fileName: file name requested by the process
 * If the disk is idle, it immediately serves the requesting process.
 * If the disk is busy, the process and requested file name
 * gets added to the I/O-queue of the disk.
 */
void Disk::addToDiskQueue( Process requesting_process, std::string fileName )
{
    if (servingProcess_.getPID() == -1) {
        servingProcess_ = requesting_process;
        servingFileName_ = fileName;
    } else {
        diskQueue_.push_back(requesting_process);
        fileQueue_.push_back(fileName);
    }
}


/**
 * @return process that finished being served by the disk.
 * The disk completes the job of serving the process.
 */
Process Disk::completeJob()
{
    if (servingProcess_.getPID() == -1) {
        return Process();
    } else if (diskQueue_.size() > 0) {
        Process completed_process = servingProcess_;
        servingProcess_ = diskQueue_.front();
        servingFileName_ = fileQueue_.front();
        diskQueue_.pop_front();
        fileQueue_.pop_front();
        return completed_process;
    } else {
        Process completed_process = servingProcess_;
        servingProcess_ = Process();
        servingFileName_ = "";
        return completed_process;
    }
}