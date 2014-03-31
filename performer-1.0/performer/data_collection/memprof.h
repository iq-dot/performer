#ifndef MEMPROF_H_INCLUDED
#define MEMPROF_H_INCLUDED

#include "pstructs.h"

class MemProfiler
{
	public:
		MemProfiler(){};
		virtual ~MemProfiler(){};

		//functions that updates readings and retrieves the results
		virtual void poll() = 0;
		virtual MemInfo getMemInfo() = 0;
};
#endif //end guard
