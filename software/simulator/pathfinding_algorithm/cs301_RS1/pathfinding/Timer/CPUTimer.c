#ifndef CPUTIMER_C
#define CPUTIMER_C

#include "CPUTimer.h"


clock_t GetCurrentClockTime()
{
	return clock();
}

int ConvertToMilliSeconds(clock_t period, clock_t error)
{
	return (int)(((period - error) * 1000) / CLOCKS_PER_SEC);
}

//printf("Time taken %d seconds %d milliseconds", msec / 1000, msec % 1000);

#endif // !CPUTIMER_C
