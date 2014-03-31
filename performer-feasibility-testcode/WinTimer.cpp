#include "WinTimer.h"

WinTimer::WinTimer()
{
	QueryPerformanceFrequency(&cpuFrequency);
	//TODO: Handle error code
}

void WinTimer::startTimer()
{
	QueryPerformanceCounter(&tStamp1);
	//TODO: Handle error code
}

void WinTImer::stopTimer()
{
	QueryPerformanceCounter(&tStamp2);

	double diff = tStamp2.quadPart - tStamp1.quadPart;
	double freq = cpuFrequency.quadPart;

	time = diff / freq;
}

double WinTimer::getTime()
{
	return time;
}