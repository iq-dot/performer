#include "performer/data_collection/linux/lintimer.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

using namespace std;

LinTimer::LinTimer():useOffset(false), wallOffset(0), cpuOffset(0), usrOffset(0), sysOffset(0)
{
    //for safety initialize struct to 0
    spdResult.wallTime=0;
    spdResult.cpuTime=0;
    spdResult.usrTime=0;
    spdResult.sysTime=0;

	// Set-up temporary variables for calculating offset values; the offset values are the cost of calling the actual
	// functions that take the time measurements
	rusage cp1;
	rusage cp2;
	getrusage(RUSAGE_SELF, &cp1);
	getrusage(RUSAGE_SELF, &cp2);

	timespec wt1;
	timespec wt2;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &wt1);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &wt2);

	// Call private functions to calculate the offset
	calcWallTime(wallOffset, wt1, wt2);
	calcCpuTime(cpuOffset, usrOffset, sysOffset, cp1, cp2);
}

LinTimer::~LinTimer()
{
}

// Takes the first timestamps and hence the first reading for calculating measured wall-clock and cpu-time
// Timestamp for cpu-time is taken first as this is less accurate then wall-clock timestamp which makes
// the wall-clock timestamp more susceptible to inaccuracies
void LinTimer::startTimer()
{
    // performs the both timestamps for wall-clock and cpu-time, these are system calls
    cpuChk1 = getrusage(RUSAGE_SELF, &cpuStamp1);
    wallChk1 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timeStamp1);
}

// Allows you take the wall-time measurement ONLY, will not take the cpu-time measurement
void LinTimer::startWallTimer()
{
    wallChk1 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timeStamp1);
}

// Allows you take ONLY the cpu-time measurement, wall-clock timestamp will not be generated
void LinTimer::startCpuTimer()
{
    cpuChk1 = getrusage(RUSAGE_SELF, &cpuStamp1);
}

// The last timestamps for both cpu and wall-clock are taken here and used to calculate the measured values
// Error codes are also checked and will retun false if any errors arise from the timestamps
bool LinTimer::stopTimer()
{
    cpuChk2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timeStamp2);
    wallChk2 = getrusage(RUSAGE_SELF, &cpuStamp2);

    // check for any error values from doing the timestamps
    if(cpuChk1 != 0 || cpuChk2 !=0 || wallChk1 != 0 || wallChk2!= 0){
        return false;
    }

    // private methods handle the calculation
    calcWallTime(spdResult.wallTime, timeStamp1, timeStamp2);
    calcCpuTime(spdResult.cpuTime, spdResult.usrTime, spdResult.sysTime, cpuStamp1, cpuStamp2);
    return true;
}

// Only call if startWallTimer was called previously, will calculate the wall-time
bool LinTimer::stopWallTimer()
{
    wallChk2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timeStamp2);

    // check for any error values from doing the timestamps
    if(wallChk1 != 0 || wallChk2!= 0){
        return false;
    }
    // private methods handle the calculation
    calcWallTime(spdResult.wallTime, timeStamp1, timeStamp2);
    return true;
}

// ONLY call this if you have previously called startCpuTimer otherwise you may get an error, will calculate cpu-time
bool LinTimer::stopCpuTimer()
{
    cpuChk2 = getrusage(RUSAGE_SELF, &cpuStamp2);

    // check for any error values from doing the timestamps
    if(cpuChk1 != 0 || cpuChk2 !=0){
        return false;
    }
    // private methods handle the calculation
    calcCpuTime(spdResult.cpuTime, spdResult.usrTime, spdResult.sysTime, cpuStamp1, cpuStamp2);
    return true;
}

//return the full results as a structure
SpeedInfo LinTimer::getResult()
{
    return spdResult;
}

// Return the measured wall-time, will be zero if it has not been calculated yet
double LinTimer::getWallTime() const
{
    return spdResult.wallTime;
}

// Return the measured cpu-time, will be zero if it has not been calculated yet
double LinTimer::getCpuTime() const
{
    return spdResult.cpuTime;
}

// Return the user-time, will be zero if it has not been calculated yet
double LinTimer::getUserTime() const
{
    return spdResult.usrTime;
}

// Returns the system-time, will be zero if it has not been calculated yet
double LinTimer::getKernelTime() const
{
    return spdResult.sysTime;
}

// Returns the measured wall time in milliseconds
double LinTimer::getWallMilliSecTime() const
{
    return spdResult.wallTime / 1000000;
}

// Returns the cpu-time in milliseconds
double LinTimer::getCpuMilliSecTime() const
{
    return spdResult.cpuTime / 1000;
}

// Returns the uesr-time in milliseconds
double LinTimer::getUserMilliSecTime() const
{
    return spdResult.usrTime / 1000;
}

// Returns the system-time in milliseconds
double LinTimer::getKernelMilliSecTime() const
{
    return spdResult.sysTime / 1000;
}

// Sets whether to use offset values for calculations
void LinTimer::setUseOffset(bool value)
{
    useOffset = value;
}

// Calculates the measured wall-clock time in nanoseconds
// Parameter information:
// wTime - will hold the calculated wall-clock time
// tStamp1 - the first recorded wall clock time stamp
// tStamp2 - the second recorded time stamp
inline void LinTimer::calcWallTime(double &wTime, const timespec &tStamp1, const timespec &tStamp2)
{
    wTime = (tStamp2.tv_nsec - tStamp1.tv_nsec);
    if(useOffset){
        wTime -= wallOffset;
    }
}

// Calculates measured user-time, system-time and total cpu-time (sum of user + system time) in microseconds
// Parameter information:
// cTime - will hold the total cpu-time
// uTime - will hold the measured user-time
// sTime - will hold the measured system-time
// cStamp1 - the first measured time-stamp
// cStamp2 - the second measured time-stamp
inline void LinTimer::calcCpuTime(double &cTime, double &uTime, double &sTime, const rusage &cStamp1, const rusage &cStamp2)
{
    uTime = (cStamp2.ru_utime.tv_usec - cStamp1.ru_utime.tv_usec);
    sTime = (cStamp2.ru_stime.tv_usec - cStamp1.ru_stime.tv_usec);
    cTime = (sTime + uTime);

    if(useOffset){
        uTime -= usrOffset;
        sTime -= sysOffset;
        cTime -= cpuOffset;
    }
}
