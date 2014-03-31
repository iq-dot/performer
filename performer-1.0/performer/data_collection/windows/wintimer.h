#ifndef WINTIMER_H_INCLUDED
#define WINTIMER_H_INCLUDED

#include <windows.h>
#include "performer/data_collection/timer.h"

/**
* This windows specific timer will retrieve timing information between the calls of start and stop functions.
* The timing information is hardware dependant and cpu registers and windows kernel will be used to retrieve information such as
* wall-time and cpu-time (split in 2 parts, user-time and kernel-time)
*/
class WinTimer: public Timer
{
    public:
        // Initialize the cpu-frequency value and calculate offset values in the constructor
        WinTimer();

        // These are the main two functions which will automatically take readings for elapsed wall clock and cpu time between
        // the start and stop timer calls
        void startTimer();
        bool stopTimer();

        // These functions are used for ONLY timing wall clock, generally for windows this is of highest precision (nanoseconds)
        void startWallTimer();
        bool stopWallTimer();

        // These functions ONLY measure CpuTime which the precision is stated to be 100ns intervals in windows
        void startCpuTimer();
        bool stopCpuTimer();

        // Gets the full result as a structure
        SpeedInfo getResult();

        // This method defines whether to use offsets or not
        void setUseOffset(bool value);

        // These functions allow you to retrieve individual final measured values of interest
        // Note that CpuTime is the total of User and Kernel time
        double getWallTime() const;
        double getCpuTime() const;
        double getUserTime() const;
        double getKernelTime() const;

        // Get the cpu frequency
        double getCpuFrequency() const;

        // These functions will retrieve values of wall-time and cpu-time converted to millseconds
        double getWallMilliSecTime() const;
        double getCpuMilliSecTime() const;
        double getUserMilliSecTime() const;
        double getKernelMilliSecTime() const;

    private:
        // Private methods for calculating the wall and cpu-times
        inline void calcWallTime(double &_wtime, const LARGE_INTEGER &_ts1, const LARGE_INTEGER &_ts2);

        void calcCpuTimes(double &_cpuTime,
                          double &_usrTime,
                          double &_sysTime,
                          const FILETIME &_usrTimeStamp1,
                          const FILETIME &_usrTimeStamp2,
                          const FILETIME &_sysTimeStamp1,
                          const FILETIME &_sysTimeStamp2);

        // These are used for storing the timestamp values for measuring wall time
        LARGE_INTEGER tStamp1;
        LARGE_INTEGER tStamp2;
        LARGE_INTEGER cpuFrequency;

        //This structure will hold the final measured result
        SpeedInfo spdResult;

         // Defines whether to use offset or not
        bool useOffset;

        // These variables will hold the measured values of executing each of the time-stamp operations which will
        // be used to off-set from the final measurements to get more accurate figures
        double wOffset;
        double cpuOffset;
        double usrOffset;
        double sysOffset;

        // These values are used to store success/error codes recieved from calling the windows api functions
        BOOL countChk1, countChk2;
        BOOL procChk1, procChk2;
        BOOL cpuFreqChk;

        // These variables are used to store the timestamps for measuring actual cpu time spent
        FILETIME usrTime1, sysTime1, createTime1, exitTime1;
        FILETIME usrTime2, sysTime2, createTime2, exitTime2;
};

#endif // WINTIMER_H_INCLUDED
