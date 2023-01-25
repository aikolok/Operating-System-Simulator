/*
	main.cpp file is for testing the SimulatedOS library.
    You can modify it to simulate different scenarios.
*/

#include "SimulatedOS.h"

int main()
{
	SimulatedOS osSim{ 1, 100, 100 };

	osSim.NewProcess(10);
	osSim.NewProcess(5);

	osSim.PrintRAM();
	// Frame	Page	PID
	// 0		0		1
	// 1		0		2
    
    osSim.NewProcess(15);
    osSim.PrintRAM();
    // Frame    Page    PID
    // 0        0        1
    // 1        0        3
 
	osSim.FetchFrom(120);
	osSim.PrintRAM();
	// Frame	Page	PID
	// 0		1		3
	// 1		0		3

	osSim.DiskReadRequested(0, "job.docx");
	osSim.PrintRAM();
	// Frame	Page	PID
	// 0		1		3
	// 1		0		1

	osSim.FetchFrom(777);
	osSim.PrintRAM();
	// Frame	Page	PID
	// 0		7		1
	// 1		0		1

	osSim.NewProcess(1);
	osSim.PrintRAM();
	// Frame	Page	PID
	// 0		7		1
	// 1		0		4

	osSim.DiskJobCompleted(0);
	osSim.PrintRAM();
    // Frame    Page    PID
    // 0        7        1
    // 1        1        3

	osSim.Exit();
	osSim.PrintRAM();
	// Frame	Page	PID
	// 0		7		1
	// 1

	osSim.FetchFrom(740);
	osSim.PrintRAM();
	// Frame	Page	PID
	// 0		7		1
	// 1

	osSim.FetchFrom(3350);
	osSim.PrintRAM();
	// Frame	Page	PID
	// 0		7		1
	// 1		33		1

	osSim.FetchFrom(740);
	osSim.PrintRAM();
    // Frame    Page    PID
    // 0        7        1
    // 1        33       1

	osSim.NewProcess(20);
	osSim.FetchFrom(100);
	osSim.PrintRAM();
    // Frame    Page    PID
    // 0        1        5
    // 1        0        5

	return 0;
}
