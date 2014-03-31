#include "performer/data_collection/resultxml.h"
#include "performer/data_collection/linux/lintimer.h"
#include "performer/data_collection/linux/linmemprof.h"
#include <iostream>

using namespace std;

int main()
{

        LinTimer lt;
        LinMemProfiler lmp;
        lt.startTimer();

        ResultXML xp("wtest.xml", "atsource");

        lt.stopTimer();
        lt.startTimer();

        xp.addSpeedResult(lt.getResult(), "xmlTest");
        xp.addMemResult(lmp.getMemInfo(), "xmlTest2");

        lmp.poll();
        lt.stopTimer();

        xp.addSpeedResult(lt.getResult(), "xmlTest");

        struct MemInfo mi = lmp.getMemInfo();
        
        cout << mi << endl;

        xp.addMemResult(mi, "xmlTest3");

        xp.save();

    return 0;
}
