#include "performer/data_collection/linux/lintimer.h"
#include "performer/data_collection/linux/linmemprof.h"
#include <iostream>

using namespace std;

int main()
{

        LinTimer lt;
        LinMemProfiler lmp;
        lt.startTimer();

        lt.stopTimer();
        lt.startTimer();

        lmp.poll();
        lt.stopTimer();

        struct MemInfo mi = lmp.getMemInfo();
        
        cout << mi << endl;

    return 0;
}
