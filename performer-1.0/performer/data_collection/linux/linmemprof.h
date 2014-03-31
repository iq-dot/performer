#ifndef LINMEMPROF_H_INCLUDED
#define LINMEMPROF_H_INCLUDED

#include <stdlib.h>
#include "performer/data_collection/memprof.h"
#include "performer/data_collection/linux/procsmaps.h"
#include "performer/data_collection/linux/procstatus.h"

class LinMemProfiler : public MemProfiler
{
	public:
		LinMemProfiler();
		LinMemProfiler(pid_t  procid);
		~LinMemProfiler();

		void poll();
		MemInfo getMemInfo();

	private:
        MemInfo memResult;
		ProcSmap smap;
		ProcStatus status;
};
#endif //end of guard
