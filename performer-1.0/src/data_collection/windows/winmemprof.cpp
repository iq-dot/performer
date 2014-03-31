#include "performer/data_collection/windows/winmemprof.h"
#include <windows.h>
#include <psapi.h>

WinMemProfiler::WinMemProfiler():memResult()
{
    //ctor
}

WinMemProfiler::~WinMemProfiler()
{
    //dtor
}

void WinMemProfiler::poll()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

    memResult.pagefaults = (pmc.PageFaultCount / 1024);
    memResult.privateMem = (pmc.PrivateUsage / 1024);
    memResult.rsSize = (pmc.WorkingSetSize / 1024);
}

MemInfo WinMemProfiler::getMemInfo()
{
	return memResult;
}

