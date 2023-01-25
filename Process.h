/******************************************************************
Title:        Home Project - Operating System Class
Student:      Alima Asanbaeva
Date:         December 4, 2022
Description:  The header file for Process class
******************************************************************/

#ifndef PROCESS_H
#define PROCESS_H


class Process {
    private:
        int priority_;
        int pid_;
        unsigned int programCounter_;
        int pageNum_;
    public:
        // Default Constructor
        Process();
        // Parameterized Constructor
        Process( int priority, int pid );
        int getPriority() const;
        int getPID() const;
        int getProgramCounter() const;
        int getPageNum() const;
        void setPageNum( int pageNumber );
        void setProgramCounter( unsigned int memoryAddress );
};
#endif // PROCESS_H