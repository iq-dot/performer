#ifndef PERF_PSTRUCTS_H_INCLUDED
#define PERF_PSTRUCTS_H_INCLUDED

#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>

#ifdef WINDOWS
#   ifdef PSTRUCT_EXPORT
#   define WINLIB __declspec(dllexport)
#   else
#   define WINLIB __declspec(dllimport)
#   endif
#   define CALLCONV __stdcall
#else
#  define WINLIB
#  define CALLCONV
#endif

/**
*This file contains the data structures and typedefs that are used throughout the framework.
*It includes structures created to hold the speed and memory results as well as typedefs of
*long complicated container structures that would be cumbersome to keep typing.
*Most of the defined structures also have cout compatible overloaders for easier printing.
*/


/**
*Holds timing information
*/
struct WINLIB SpeedInfo{

    double wallTime; //holds the wall time value
    double cpuTime; //holds the total cpu time value
    double usrTime; //holds the user time value of the cpu time
    double sysTime; //holds the kernel/system time value of the cpu time

    SpeedInfo():wallTime(0), cpuTime(0), usrTime(0), sysTime(0){}
};

/**
*Holds memory information
*/
struct WINLIB MemInfo{

	int sharedMem; //total memory that makes up for shared memory (shareable with other processes)
	int privateMem; //total memory that accounts for private non-shared memory
	int dirtyMem; //total amount of memory that has been dirties, i.e. modified
	int cleanMem; //total amount of memory that is still clean, i.e. un-modified
	int swapMem; //total amount of memory that makes up for swap memory consumption
	int refMem; //the amount of memory that is actually referenced
	int sharedDirtyMem; //amount of shared memory that has been dirtied
	int sharedCleanMem; //amount of shared memory that is still clean
	int privateDirtyMem; //amount of private memory that has been dirtied
	int privateCleanMem; //amount of private memory that is still clean
	int rsSize; //amount of total memory that is resident in physical memory
	int vsSize; //the total address space of the process including swap space and resident

	int stackSize; //total memory occupied by the stack
	int stackRss; //total stack space in physical memory
	int stackRef; //total stack space that is referenced
	int stackClean; //total stack space that is clean
	int stackDirty; //total stack space that is dirty

	int heapSize; //total memory occupied by the heap
	int heapRss; //total heap space in physical memory
	int heapRef; //total heap space that is referenced
	int heapClean; //heap space that is clean
	int heapDirty; //heap space that is dirty

	int vmData; //total memory occupied by non-executable data
	int vmExe; //memory occupied for executable code
	int vmLib; //amount of memory dedicated to shared libraries
	int vmPTE; //amount of memory used for Page Table Entry

	int pagefaults; //number of page faults

	MemInfo():sharedMem(0), privateMem(0), dirtyMem(0), cleanMem(0), swapMem(0), refMem(0), sharedDirtyMem(0), sharedCleanMem(0), privateDirtyMem(0),
              privateCleanMem(0), rsSize(0), vsSize(0), stackSize(0), stackRss(0), stackRef(0), stackClean(0), stackDirty(0), heapSize(0), heapRss(0),
              heapRef(0), heapClean(0), heapDirty(0), vmData(0), vmExe(0), vmLib(0), vmPTE(0), pagefaults(0){}
};

/**
*Can be used to store both speed and memory results
*/
struct WINLIB ResultInfo{
    struct SpeedInfo si;
    struct MemInfo mi;
};

//used for storing results sorted by section names
typedef std::map<std::string, std::vector<SpeedInfo> > speed_map;
typedef std::map<std::string, std::vector<MemInfo> > mem_map;

//used for storing processed results
typedef std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, double> > > > analyzed_result;
typedef std::map<std::string, std::map<std::string, double> > result_category;

//a unique string set, mainly used for storing and printing section lists
typedef std::set<std::string> ustring_set;

//operator overloading for stream operation
WINLIB std::ostream& CALLCONV operator<<(std::ostream &st, const SpeedInfo &si);
WINLIB std::ostream& CALLCONV operator<<(std::ostream &st, const MemInfo &mi);
WINLIB std::ostream& CALLCONV operator<<(std::ostream &st, const ResultInfo &ri);
WINLIB std::ostream& CALLCONV operator<<(std::ostream &st, const analyzed_result&);
WINLIB std::ostream& CALLCONV operator<<(std::ostream &st, const ustring_set&);
WINLIB std::ostream& CALLCONV operator<<(std::ostream &st, const speed_map&);
WINLIB std::ostream& CALLCONV operator<<(std::ostream &st, const mem_map&);

//operator overloading on MemInfo and SpeedInfofor mathematical operations
WINLIB SpeedInfo CALLCONV operator+(SpeedInfo &si, SpeedInfo &si2);
WINLIB SpeedInfo& CALLCONV operator+=(SpeedInfo &si, SpeedInfo &si2);
WINLIB SpeedInfo CALLCONV operator-(SpeedInfo &si, SpeedInfo &si2);
WINLIB SpeedInfo& CALLCONV operator-=(SpeedInfo &si, SpeedInfo &si2);

WINLIB MemInfo CALLCONV operator+(MemInfo &mi, MemInfo &mi2);
WINLIB MemInfo& CALLCONV operator+=(MemInfo &mi, MemInfo &mi2);
WINLIB MemInfo CALLCONV operator-(MemInfo &mi, MemInfo &mi2);
WINLIB MemInfo& CALLCONV operator-=(MemInfo &mi, MemInfo &mi2);

#endif // PSTRUCTS_H_INCLUDED

