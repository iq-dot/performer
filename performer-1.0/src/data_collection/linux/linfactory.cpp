#include "performer/data_collection/linux/linfactory.h"
#include "performer/data_collection/linux/lintimer.h"
#include "performer/data_collection/linux/linmemprof.h"

LinFactory::LinFactory()
{
    //ctor
}

LinFactory::~LinFactory()
{
    //dtor
}

/** @brief return a linux specific timer class for speed measurement
*/
Timer* LinFactory::createTimer()
{
    return new LinTimer;
}

/** @brief return a linux spcecific memory profiler class for memory measurement
*/
MemProfiler* LinFactory::createMemProfiler()
{
    return new LinMemProfiler;
}

