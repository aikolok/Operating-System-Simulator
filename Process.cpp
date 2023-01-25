/******************************************************************
Title:        Home Project - Operating System Class
Student:      Alima Asanbaeva
Date:         December 4, 2022
Description:  The implementation file for Process class
******************************************************************/

#include "Process.h"


/**
 * Default Constructor
 * All member variables are initialized with -1.
 */
Process::Process() : priority_(-1), pid_(-1), programCounter_(-1), pageNum_(-1)
{}


/**
 * Parameterized Constructor
 * @param priority: process's priority number
 * Updates member variables with given parameter
 * Program counter and page number are set to 0 each.
 */
Process::Process( int priority, int pid ) : priority_(priority), pid_(pid)
{
    programCounter_ = 0;
    pageNum_ = 0;
}


/**
 * @return priority number of the process.
 */
int Process::getPriority() const 
{
    return priority_;
}


/**
 * @return PID of the process.
 */
int Process::getPID() const
{
    return pid_;
}


/**
 * @return program counter of the process.
 */
int Process::getProgramCounter() const
{
    return programCounter_;
}


/**
 * @return page number used by the process.
 */
int Process::getPageNum() const
{
    return pageNum_;
}


/**
 * @param pageNumber: page number
 * Set page number
 */
void Process::setPageNum( int pageNumber )
{
    pageNum_ = pageNumber;
}


/**
 * @param memoryAddress: memory address
 * Set the program counter with given memory address
 */
void Process::setProgramCounter( unsigned int memoryAddress )
{
    programCounter_ = memoryAddress;
}