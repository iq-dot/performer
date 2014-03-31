#ifndef PSTRUCTS_H_INCLUDED
#define PSTRUCTS_H_INCLUDED

struct SpeedInfo{
    double wallTime;
    double cpuTime;
    double usrTime;
    double sysTime;
};

struct MemInfo{
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
};

#endif // PSTRUCTS_H_INCLUDED
