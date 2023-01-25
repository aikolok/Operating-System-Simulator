/******************************************************************
Title:        Home Project - Operating System Class
Student:      Alima Asanbaeva
Date:         December 4, 2022
Description:  The implementation file for RAM class
******************************************************************/

#include "RAM.h"
#include <iostream>
#include <iomanip>


/**
 * Default Constructor
 * All member variables are initialized with 0.
 */
RAM::RAM() : numOfFrames_(0), timeStampCounter_(0), numOfProcessesInMem_(0)
{}


/**
 * @param numOfFrames: number of frames in the system
 * Sets up RAM capacity with given number of frames of the system 
 */
void RAM::setSize( int numOfFrames )
{
    RAMmemory_.resize(numOfFrames);
    numOfProcessesInMem_ = 0;
    numOfFrames_ = numOfFrames;
}


/**
 * Prints out the current screenshot of the RAM.
 * Format: Frame number, Page Number, Process PID.
 */
void RAM::print() const
{
    std::cout << "Frame" << std::setw (11) << "Page" << std::setw (10) << "PID" << std::endl;
    for (int i = 0; i < RAMmemory_.size(); ++i)
    {
        std::cout << std::setw (3) << i;
        if (RAMmemory_[i].getPageNum() != -1) {
            std::cout << std::setw (13) << RAMmemory_[i].getPageNum();
        } else {
            std::cout << std::setw (13) << "";
        }
        if (RAMmemory_[i].getProcessPID() != -1) {
            std::cout << std::setw (10) << RAMmemory_[i].getProcessPID() << std::endl;
        } else {
            std::cout << std::setw (10) << "" << std::endl;
        } 
    }
    std::cout << std::endl; 
}


/**
 * @param currentProcess: currently running process in the CPU
 * Updates the time stamp of the current process (with 
 * the most recently used page number).
 */
void RAM::updateTimeStamp( Process currentProcess )
{
    for (int i = 0; i < RAMmemory_.size(); ++i)
    {
        if (RAMmemory_[i].getProcessPID() == currentProcess.getPID() 
        && RAMmemory_[i].getPageNum() == currentProcess.getPageNum()) {
            RAMmemory_[i].setTimeStamp(timeStampCounter_);
            timeStampCounter_++;
        }
    }
}


/**
 * @param new_process: new process 
 * @param currentProcess: currently running process in the CPU
 * Adds new process to the RAM and updates time stamps accordingly.
 */
void RAM::addNewProcess( Process new_process, Process currentProcess )
{
    if (numOfProcessesInMem_ < numOfFrames_) {
        numOfProcessesInMem_++;
        bool found = false;
        int i = 0;
        while(!found) {
            if (RAMmemory_[i].getProcessPID() == -1) {
                RAMmemory_[i].setPageNum(new_process.getPageNum());
                RAMmemory_[i].setProcessPID(new_process.getPID());
                RAMmemory_[i].setTimeStamp(timeStampCounter_);
                timeStampCounter_++;
                if (new_process.getPID() != currentProcess.getPID()
                && currentProcess.getPID() != -1) {
                    updateTimeStamp(currentProcess);
                }
                found = true;
            } else {
                i++;
            }
        }
    } else {
        updateMemory(new_process);
        if (new_process.getPID() != currentProcess.getPID()
        && currentProcess.getPID() != -1) {
            updateTimeStamp(currentProcess);
        }
    }
}


/**
 * @param new_process: new process 
 * Replaces the process with the lowest time stamp in the RAM
 * with new process.
 */
void RAM::updateMemory(Process new_process)
{
    int removePID = -1;
    int lowestTimeStamp = timeStampCounter_;
    for (int i = 0; i < RAMmemory_.size(); ++i)
    {
        if (RAMmemory_[i].getTimeStamp() < lowestTimeStamp) {
            lowestTimeStamp = RAMmemory_[i].getTimeStamp();
            removePID = i;
        }
    }
    RAMmemory_[removePID].setProcessPID(new_process.getPID());
    RAMmemory_[removePID].setPageNum(new_process.getPageNum());
    RAMmemory_[removePID].setTimeStamp(timeStampCounter_);
    timeStampCounter_++;
}


/**
 * @param terminatedProcess: terminated process 
 * Removes all the records of the terminated process
 * from the RAM.
 */
void RAM::remove_process( Process terminatedProcess )
{
    for (int i = 0; i < RAMmemory_.size(); ++i)
    {
        if (RAMmemory_[i].getProcessPID() == terminatedProcess.getPID()) {
            RAMmemory_[i].setProcessPID(-1);
            RAMmemory_[i].setPageNum(-1);
            numOfProcessesInMem_--;
        }
    }
}


/**
 * @param currentProcess: currently running process in the CPU 
 * Updates the record of the process in the RAM.
 */
void RAM::updateProcess( Process currentProcess )
{
    bool alreadyExists = false;
    for (int i = 0; i < RAMmemory_.size(); ++i)
    {
        if (RAMmemory_[i].getProcessPID() == currentProcess.getPID() 
        && RAMmemory_[i].getPageNum() == currentProcess.getPageNum()) {
            RAMmemory_[i].setTimeStamp(timeStampCounter_);
            timeStampCounter_++;
            alreadyExists = true;
        }
    }
    if (!alreadyExists) {
        addNewProcess(currentProcess, Process());
    }
}