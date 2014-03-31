#ifndef WINMEMPROFILER_H
#define WINMEMPROFILER_H

#include <performer/data_collection/memprof.h>

class WinMemProfiler : public MemProfiler
{
    public:
        WinMemProfiler();
        virtual ~WinMemProfiler();

        //functions for taking a memory snapshot of the current process and return the result as a MemInfo structure
        void poll();
        MemInfo getMemInfo();

    private:
        MemInfo memResult;
};
#endif // WINMEMPROFILER_H

