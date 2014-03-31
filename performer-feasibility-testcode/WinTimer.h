#ifndef WINTIMER_H_INCLUDED
#define WINTIMER_H_INCLUDED

#include <windows.h>
#include "Timer.h"

class WinTimer: public Timer
{
private:
	LARGE_INTEGER tStamp1, tStamp2, cpuFrequency;
	double time;

	FILETIME cpuTime, sysTime, createTime, exitTime;
	FILETIME cpuTime2, sysTime2, createTime2, exitTime2;

public:
	WinTimer();
	void startTimer();
	void stopTimer();
	double getTime();
};

#endif // WINTIMER_H_INCLUDED
