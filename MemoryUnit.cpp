/******************************************************************
Title:        Home Project - Operating System Class
Student:      Alima Asanbaeva
Date:         December 4, 2022
Description:  The implementation file for MemoryUnit class
******************************************************************/

#include "MemoryUnit.h"
#include <iostream>


/**
 * Default Constructor
 * All the member variables are set to -1.
 */
MemoryUnit::MemoryUnit() : pageNum_(-1), processPID_(-1), timeStamp_(-1)
{}


/**
 * Parameterized Constructor
 * @param pageNum: page number used by the process
 * @param processPID: process PID
 * @param timeStamp: integer time stamp 
 * All member variables are updated with the given parameters.
 */
MemoryUnit::MemoryUnit( int pageNum, int processPID, int timeStamp ) : pageNum_(pageNum), processPID_(processPID), timeStamp_(timeStamp)
{}


/**
 * @return the page number
 */
int MemoryUnit::getPageNum() const
{
    return pageNum_;
}


/**
 * @return the process PID
 */
int MemoryUnit::getProcessPID() const
{
    return processPID_;
}


/**
 * @return the integer time stamp
 */
int MemoryUnit::getTimeStamp() const
{
    return timeStamp_;
}


/**
 * @param pageNumber: new page number used by the process
 * Set page number
 */
void MemoryUnit::setPageNum( int pageNumber )
{
    pageNum_ = pageNumber;
}


/**
 * @param PID: process PID
 * Set process PID
 */
void MemoryUnit::setProcessPID( int PID )
{
    processPID_ = PID;
}


/**
 * @param timeStamp: integer time stamp
 * Set time stamp
 */
void MemoryUnit::setTimeStamp( int timeStamp )
{
    timeStamp_ = timeStamp;
}