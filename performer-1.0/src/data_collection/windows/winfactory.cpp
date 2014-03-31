#include "performer/data_collection/windows/winfactory.h"
#include "performer/data_collection/windows/wintimer.h"
#include "performer/data_collection/windows/winmemprof.h"

WinFactory::WinFactory()
{
    //ctor
}

WinFactory::~WinFactory()
{
    //dtor
}

/** @brief return a windows specific timer class for speed measurement
*/
Timer* WinFactory::createTimer()
{
    return new WinTimer;
}

/** @brief return a windows specific memory profiler class for memory measurement
*/
MemProfiler* WinFactory::createMemProfiler()
{
    return new WinMemProfiler;
}
