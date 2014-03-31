#include "performer/data_collection/windows/wintimer.h"

// The constructor will initialize the cpu frequency value and calculate the off-sets
WinTimer::WinTimer():cpuOffset(0), usrOffset(0), sysOffset(0)
{
    //for safety initialize struct to 0
    spdResult.wallTime=0;
    spdResult.cpuTime=0;
    spdResult.usrTime=0;
    spdResult.sysTime=0;

	cpuFreqChk = QueryPerformanceFrequency(&cpuFrequency); //intialize the cpu frequency value

	LARGE_INTEGER ts1;
	LARGE_INTEGER ts2;

	// estimate the offset values for wall-time, i.e. the cost of the actual system call
	QueryPerformanceCounter(&ts1);
	QueryPerformanceCounter(&ts2);

	WinTimer::calcWallTime(wOffset, ts1, ts2);

	// estimate the offset values for cpu-time, i.e. the cost of the actual system calls
	FILETIME create1, exit1, sys1, usr1;
	FILETIME create2, exit2, sys2, usr2;

	GetProcessTimes(GetCurrentProcess(), (FILETIME*)&create1, (FILETIME*)&exit1, (FILETIME*)&sys1, (FILETIME*)&usr1);
	GetProcessTimes(GetCurrentProcess(), (FILETIME*)&create2, (FILETIME*)&exit2, (FILETIME*)&sys2, (FILETIME*)&usr2);

	WinTimer::calcCpuTimes(cpuOffset, usrOffset, sysOffset, usr1, usr2, sys1, sys2);
}

// This will create the first time-stamp for measuring wall-clock and cpu-time, it will use high precision counters retrieved
// from hardware usually cpu registers using the windows API, this is hardware and OS dependant.
// The time-stamp for wall-clock has been called AFTER the time-stamp for cpu-time because the wall-clock
// measure is of much higher accuracy and more susceptible to measurement inaccuracies
void WinTimer::startTimer()
{
    procChk1 = GetProcessTimes(GetCurrentProcess(),
                               (FILETIME*)&createTime1,
                               (FILETIME*)&exitTime1,
                               (FILETIME*)&sysTime1,
                               (FILETIME*)&usrTime1);

	countChk1 = QueryPerformanceCounter(&tStamp1); //This is the wall-clock time-stamp while the above is for cpu-time
}

// Start ONLY the wall-timer and NOT the cpu-timer
void WinTimer::startWallTimer()
{
	countChk1 = QueryPerformanceCounter(&tStamp1);
}

// Start ONLY the cpu-timer and NOT the wall-timer
void WinTimer::startCpuTimer()
{
	procChk1 = GetProcessTimes(GetCurrentProcess(),
                               (FILETIME*)&createTime1,
                               (FILETIME*)&exitTime1,
                               (FILETIME*)&sysTime1,
                               (FILETIME*)&usrTime1);
}

// This will create the last time-stamp for both wall-clock and cpu-time and will calculate the measurements.
// Call this ONLY when you called startTimer() previously.
// The order of time-stamp is important, wall-clock time-stamp is executed first to prevent any influences from other in-between operation calls.
// Error codes are also checked at this stage and notified to user, it is checked now and not before to prevent any
// timing in-accuracies caused by doing checks in-between the start and stop calls.
bool WinTimer::stopTimer()
{
	countChk2 = QueryPerformanceCounter(&tStamp2);
	procChk2 = GetProcessTimes(GetCurrentProcess(),
                               (FILETIME*)&createTime2,
                               (FILETIME*)&exitTime2,
                               (FILETIME*)&sysTime2,
                               (FILETIME*)&usrTime2);

	// Check for any error codes
	if(countChk1 == FALSE || countChk2 == FALSE || procChk1 == FALSE || procChk2 == FALSE || cpuFreqChk == FALSE){
		return false;
	}

	// call private functions to do the calculations
	WinTimer::calcWallTime(spdResult.wallTime, tStamp1, tStamp2);
	WinTimer::calcCpuTimes(spdResult.cpuTime, spdResult.usrTime, spdResult.sysTime, usrTime1, usrTime2, sysTime1, sysTime2);

	return true;
}

// Stop the wall-timer, call this ONLY when you previously called startWallTimer(), otherwise you may get errors
bool WinTimer::stopWallTimer()
{
	countChk2 = QueryPerformanceCounter(&tStamp2);

	// Check for any error codes
	if(countChk1 == FALSE || countChk2 == FALSE || cpuFreqChk == FALSE){
		return false;
	}
	WinTimer::calcWallTime(spdResult.wallTime, tStamp1, tStamp2);

	return true;
}

// Stop the cpu-timer, call this ONLY when you previously called startCpuTimer(), otherwise you may get errors
bool WinTimer::stopCpuTimer()
{
	procChk2 = GetProcessTimes(GetCurrentProcess(),
                               (FILETIME*)&createTime2,
                               (FILETIME*)&exitTime2,
                               (FILETIME*)&sysTime2,
                               (FILETIME*)&usrTime2);

    // Check for any error codes
	if(procChk1 == FALSE || procChk2 == FALSE){
		return false;
	}
	WinTimer::calcCpuTimes(spdResult.cpuTime, spdResult.usrTime, spdResult.sysTime, usrTime1, usrTime2, sysTime1, sysTime2);

	return true;
}

//return the full result as a structure
SpeedInfo WinTimer::getResult()
{
    return spdResult;
}

// Sets whether to use offset values for calculations
void LinTimer::setUseOffset(bool value)
{
    useOffset = value;
}

// Return elapsed wall-time
double WinTimer::getWallTime() const
{
	return spdResult.wallTime;
}

// Return total cpu-time
double WinTimer::getCpuTime() const
{
	return spdResult.cpuTime;
}

// Return amount of user cpu time spent
double WinTimer::getUserTime() const
{
	return spdResult.usrTime;
}

// Return amount of system cpu time spent
double WinTimer::getKernelTime() const
{
	return spdResult.sysTime;
}

// Convert and return wall-time in milliseconds (1000th of a second)
double WinTimer::getWallMilliSecTime() const
{
	return spdResult.wallTime / 1000000;
}

// Convert and return total cpu-time in milliseconds (1000th of a second)
double WinTimer::getCpuMilliSecTime() const
{
	return spdResult.cpuTime / 1000000;
}

// Convert and return user cpu-time in milliseconds (1000th of a second)
double WinTimer::getUserMilliSecTime() const
{
	return spdResult.usrTime / 1000000;
}

// Convert and return system cpu-time in milliseconds (1000th of a second)
double WinTimer::getKernelMilliSecTime() const
{
	return spdResult.sysTime / 1000000;
}

// Return the cpu frequency value as a double
double WinTimer::getCpuFrequency() const
{
	return double(cpuFrequency.QuadPart);
}

// Calculate wall-time based on the parameters passed in, here is a quick overview of each parameter:
// _wtime - variable to hold the calculated wall-time
// _ts1 - the first time-stamp
// _ts2 - the second time-stamp
void WinTimer::calcWallTime(double &_wTime, const LARGE_INTEGER &_ts1, const LARGE_INTEGER &_ts2)
{
	//calculate wall time
	double diff = _ts2.QuadPart - _ts1.QuadPart;
	_wTime = diff / WinTimer::getCpuFrequency();

	if(useOffset){
	    _wTime - cpuOffset;
	}
}

// Calculate all cpu-times based on the parameters passed in, here is a quick overview of each parameter:
// _ctime - variable to store the total cpu-time
// _utime - varaible to store the user cpu-time
// _stime - variable to store teh system cpu-time
// _usr1 - first timestamp for user cpu-time
// _usr2 - second timestamp for user cpu-time
// _sys1 - first timestamp for system cpu-time
// _sys2 - second timestamp for system cpu-time
void WinTimer::calcCpuTimes(double &_ctime,
                            double &_utime,
                            double &_stime,
                            const FILETIME &_usr1,
                            const FILETIME &_usr2,
                            const FILETIME &_sys1,
                            const FILETIME &_sys2){
	// calculate cpu time, need to convert FILETIME to LARGE_INTEGER for arithmetic and then convert back to FILETIME
	LARGE_INTEGER usr1;
	LARGE_INTEGER usr2;
	LARGE_INTEGER sys1;
	LARGE_INTEGER sys2;

	// total cpu-time at both time-stamps
	LARGE_INTEGER totCpu1;
	LARGE_INTEGER totCpu2;

	// difference value between the time-stamps
	LARGE_INTEGER diffUsr;
	LARGE_INTEGER diffSys;
	LARGE_INTEGER diffTotCpu;

	usr1.HighPart = _usr1.dwHighDateTime;
	usr1.LowPart = _usr1.dwLowDateTime;
	sys1.HighPart = _sys1.dwHighDateTime;
	sys1.LowPart = _sys1.dwLowDateTime;

	totCpu1.QuadPart = usr1.QuadPart + sys1.QuadPart; // total cpu-time from 1st time-stamp

	usr2.HighPart = _usr2.dwHighDateTime;
	usr2.LowPart = _usr2.dwLowDateTime;
	sys2.HighPart = _sys2.dwHighDateTime;
	sys2.LowPart = _sys2.dwLowDateTime;

	totCpu2.QuadPart = usr2.QuadPart + sys2.QuadPart; // total cpu-time from 2nd time-stamp

	// get the value difference for user, system and total cpu-time between the time-stamps
	diffUsr.QuadPart = usr2.QuadPart - usr1.QuadPart;
	diffSys.QuadPart = sys2.QuadPart - sys1.QuadPart;
	diffTotCpu.QuadPart = totCpu2.QuadPart - totCpu1.QuadPart;

	// times by 100 to standardize to nanosecond instead of 100ns
	_utime = (diffUsr.QuadPart * 100);
	_stime = (diffSys.QuadPart * 100);
	_ctime = (diffTotCpu.QuadPart * 100);

	if(useOffset){
	    _utime -= usrOffset;
	    _stime -= sysOffset;
	    _ctime -= cpuOffset;
	}
}
