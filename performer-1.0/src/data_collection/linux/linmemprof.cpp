#include <stdlib.h>
#include "performer/data_collection/linux/linmemprof.h"

LinMemProfiler::LinMemProfiler():memResult(), smap(memResult), status(memResult)
{

}

LinMemProfiler::LinMemProfiler(pid_t procid):smap(memResult, procid), status(memResult, procid)
{

}

LinMemProfiler::~LinMemProfiler()
{
}

void LinMemProfiler::poll()
{
	smap.update(memResult);
	status.update(memResult);
}

MemInfo LinMemProfiler::getMemInfo()
{
	return memResult;
}
