#ifndef CPUTIMER_H
#define CPUTIMER_H

/*
	CPU Timer

	A simple utility module for finding the CPU time.
*/

#include <time.h>


clock_t GetCurrentClockTime();

// The error is the timing overhead.
int ConvertToMilliSeconds(clock_t period, clock_t error);


#endif // !CPUTIMER_H
