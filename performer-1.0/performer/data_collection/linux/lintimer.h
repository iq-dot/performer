#ifndef LINTIMER_H_INCLUDED
#define LINTIMER_H_INCLUDED

#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>
#include "performer/data_collection/timer.h"

/**
* This linux specific timer will retrieve timing information between the calls of start and stop functions.
* The timing information and its accuracy is hardware dependant and OS dependant, the kernel will be used to retrieve information
* such as wall-time and cpu-time (split in 2 parts, user-time and kernel-time)
*/
class LinTimer: public Timer
{
    public:
        // Initialize and calculate offset values in the constructor
        LinTimer();
        ~LinTimer();

        // These are the main two functions which will automatically take readings for elapsed wall clock and cpu time between
        // the start and stop timer calls
        void startTimer();
        bool stopTimer();

        // These functions are used for ONLY timing wall clock, in linux, depending on hardware this is of highest precision (nanoseconds)
        void startWallTimer();
        bool stopWallTimer();

        // These functions ONLY measure CpuTime which the precision in linux can vary a little but is usually in microseconds
        void startCpuTimer();
        bool stopCpuTimer();

        // This method defines whether to use offsets or not
        void setUseOffset(bool value);

        // Gets the full result as a structure
        SpeedInfo getResult();

        // These functions allow you to retrieve individual final measured values of interest
        // Note that CpuTime is the total of User and Kernel time
        double getWallTime() const;
        double getCpuTime() const;
        double getUserTime() const;
        double getKernelTime() const;

        // These functions will retrieve values of wall-time and cpu-time converted to millseconds
        double getWallMilliSecTime() const;
        double getCpuMilliSecTime() const;
        double getUserMilliSecTime() const;
        double getKernelMilliSecTime() const;

    private:
        // These private functions calculate the wall and cpu time from the given time and cpu stamps
        void calcWallTime(double &wTime, const timespec &tStamp1, const timespec &tStamp2);
        void calcCpuTime(double &cTime, double &uTime, double &sTime, const rusage &cStamp1, const rusage &cStamp2);

        // The timestamps for wall-time and cpu-time which are used to get the wall and cpu-time measurements
        timespec timeStamp1;
        timespec timeStamp2;
        rusage cpuStamp1;
        rusage cpuStamp2;

        // The final measured value for wall-time and cpu-time will be stored in this structure
        SpeedInfo spdResult;

        // Defines whether to use offset or not
        bool useOffset;

        // These are the offset values, in other words the cost of calling the operations to do the measurements
        double wallOffset;
        double cpuOffset;
        double usrOffset;
        double sysOffset;

        // These values will hold the return values which are error codes returned when doing the timestamps
        int wallChk1;
        int wallChk2;
        int cpuChk1;
        int cpuChk2;
};
#endif // LINTIMER_H_INCLUDED
