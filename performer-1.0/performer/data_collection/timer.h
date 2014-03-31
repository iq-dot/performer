#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "performer/data_collection/pstructs.h"

/**
* This abstract class defines the basic functionality expected from a timer implementation.
* It is expected this will be implemented in platform-specific versions in order to achieve accurate timers.
*/
class Timer
{
public:
    Timer(){};
    virtual ~Timer(){};

	// These functions are expected to measure both wall-clock and cpu-time
	virtual void startTimer()=0;
	virtual bool stopTimer()=0;

	// Give flexiblity in measuring just wall-clock time
	virtual void startWallTimer() = 0;
	virtual bool stopWallTimer() = 0;

	// Give flexibility in measuring just cpu-time
	virtual void startCpuTimer() = 0;
	virtual bool stopCpuTimer() = 0;

	// Gets the full result as a structure
	virtual SpeedInfo getResult() = 0;

	// Timers should be have an option to enable or disable the use of offset in calculations
	virtual void setUseOffset(bool val) = 0;

	// Allow the ability to retrieve specific final measured values in terms of wall-clock and cpu-time
	// Cpu-time can be broken down into user and kernel time
	virtual double getWallTime() const = 0;
	virtual double getCpuTime() const = 0;
	virtual double getUserTime() const = 0;
	virtual double getKernelTime() const = 0;

	// Convert and retrieve values as milliseconds
	virtual double getWallMilliSecTime() const = 0;
	virtual double getCpuMilliSecTime() const = 0;
	virtual double getUserMilliSecTime() const = 0;
	virtual double getKernelMilliSecTime() const = 0;
};

#endif // TIMER_H_INCLUDED
