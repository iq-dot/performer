#include "performer/analysis/pstddeviation.h"
#include <cmath>

using namespace std;

/**
*Default constructor, initializes base constructor and all state values to 0
*/
PstdDeviation::PstdDeviation(result_category *rc):PerformerFunctor("Std-Deviation", rc), spd_nsize(0), mem_nsize(0), sumWallTime(0), sumCpuTime(0), sumUsrTime(0),
    sumSysTime(0), sumVsSize(0), sumRsSize(0), sumRefMem(0), sumSwapMem(0), sumCleanMem(0), sumDirtyMem(0), sumPrivateMem(0), sumPrivateCleanMem(0),
    sumPrivateDirtyMem(0), sumSharedMem(0), sumSharedCleanMem(0), sumSharedDirtyMem(0), sumStackSize(0), sumStackRss(0), sumStackRef(0), sumStackClean(0),
    sumStackDirty(0), sumHeapSize(0), sumHeapRss(0), sumHeapRef(0), sumHeapClean(0), sumHeapDirty(0), sumVmData(0), sumVmExe(0), sumVmLib(0), sumVmPTE(0), sumPagefaults(0)
{
    //ctor
}

PstdDeviation::~PstdDeviation()
{
    //dtor
}

/**
*Calculate standard deviation of speed info
*/
void PstdDeviation::operator()(const SpeedInfo &si)
{
    spd_nsize++;

    //divide by 1million is needed to make squaring possible as the values will be too high

    double siWall = si.wallTime;
    double siCpu = si.cpuTime;
    double siUsr = si.usrTime;
    double siSys = si.sysTime;

    double avgWall = (*rc)["average"]["wallTime"];
    double avgCpu = (*rc)["average"]["cpuTime"];
    double avgUsr = (*rc)["average"]["usrTime"];
    double avgSys = (*rc)["average"]["sysTime"];

    sumWallTime += pow(((siWall - avgWall) / 1000000),2);
    sumCpuTime += pow(((siCpu - avgCpu) / 1000000),2);
    sumUsrTime += pow(((siUsr - avgUsr) / 1000000),2);
    sumSysTime +=  pow(((siSys - avgSys) / 1000000),2);

    (*rc)["std-deviation"]["wallTime"] = static_cast<double>(sqrt((sumWallTime / spd_nsize)) * 1000000);
    (*rc)["std-deviation"]["cpuTime"] = static_cast<double>(sqrt((sumCpuTime / spd_nsize)) * 1000000);
    (*rc)["std-deviation"]["usrTime"] = static_cast<double>(sqrt((sumUsrTime / spd_nsize)) * 1000000);
    (*rc)["std-deviation"]["sysTime"] = static_cast<double>(sqrt((sumSysTime / spd_nsize)) * 1000000);
}

/**
*Calculate standard deviation of memory results
*/
void PstdDeviation::operator()(const MemInfo &mi)
{
    mem_nsize++;

    sumVsSize += pow((mi.vsSize-(*rc)["average"]["vsSize"]),2);
    sumRsSize += pow((mi.rsSize-(*rc)["average"]["rsSize"]),2);
    sumRefMem += pow((mi.refMem-(*rc)["average"]["refMem"]),2);
    sumSwapMem += pow((mi.swapMem-(*rc)["average"]["swapMem"]),2);

    sumCleanMem += pow((mi.cleanMem-(*rc)["average"]["cleanMem"]),2);
    sumDirtyMem += pow((mi.dirtyMem-(*rc)["average"]["dirtyMem"]),2);

    sumPrivateMem += pow((mi.privateMem-(*rc)["average"]["privateMem"]),2);
    sumPrivateCleanMem += pow((mi.privateCleanMem-(*rc)["average"]["privateCleanMem"]),2);
    sumPrivateDirtyMem += pow((mi.privateDirtyMem-(*rc)["average"]["privateDirtyMem"]),2);

    sumSharedMem += pow((mi.sharedMem-(*rc)["average"]["sharedMem"]),2);
    sumSharedCleanMem += pow((mi.sharedCleanMem-(*rc)["average"]["sharedCleanMem"]),2);
    sumSharedDirtyMem += pow((mi.sharedDirtyMem-(*rc)["average"]["sharedDirtyMem"]),2);

    sumStackSize += pow((mi.stackSize-(*rc)["average"]["stackSize"]),2);
    sumStackRss += pow((mi.stackRss-(*rc)["average"]["stackRss"]),2);
    sumStackRef += pow((mi.stackRef-(*rc)["average"]["stackRef"]),2);
    sumStackClean += pow((mi.stackClean-(*rc)["average"]["stackClean"]),2);
    sumStackDirty += pow((mi.stackDirty-(*rc)["average"]["stackDirty"]),2);

    sumHeapSize += pow((mi.heapSize-(*rc)["average"]["heapSize"]),2);
    sumHeapRss += pow((mi.heapRss-(*rc)["average"]["heapRss"]),2);
    sumHeapRef += pow((mi.heapRss-(*rc)["average"]["heapRef"]),2);
    sumHeapClean += pow((mi.heapClean-(*rc)["average"]["heapClean"]),2);
    sumHeapDirty += pow((mi.heapDirty-(*rc)["average"]["heapDirty"]),2);

    sumVmData += pow((mi.vmData-(*rc)["average"]["vmData"]),2);
    sumVmExe += pow((mi.vmExe-(*rc)["average"]["vmExe"]),2);
    sumVmLib += pow((mi.vmLib-(*rc)["average"]["vmLib"]),2);
    sumVmPTE += pow((mi.vmPTE-(*rc)["average"]["vmPTE"]),2);

    sumPagefaults += pow((mi.pagefaults-(*rc)["average"]["pagefaults"]),2);

    (*rc)["std-deviation"]["vsSize"] = static_cast<double>(sqrt(sumVsSize / mem_nsize));
    (*rc)["std-deviation"]["rsSize"] = static_cast<double>(sqrt(sumRsSize / mem_nsize));
    (*rc)["std-deviation"]["refMem"] = static_cast<double>(sqrt(sumRefMem / mem_nsize));
    (*rc)["std-deviation"]["swapMem"] = static_cast<double>(sqrt(sumSwapMem / mem_nsize));

    (*rc)["std-deviation"]["cleanMem"] = static_cast<double>(sqrt(sumCleanMem / mem_nsize));
    (*rc)["std-deviation"]["dirtyMem"] = static_cast<double>(sqrt(sumDirtyMem / mem_nsize));

    (*rc)["std-deviation"]["privateMem"] = static_cast<double>(sqrt(sumPrivateMem / mem_nsize));
    (*rc)["std-deviation"]["privateCleanMem"] = static_cast<double>(sqrt(sumPrivateCleanMem / mem_nsize));
    (*rc)["std-deviation"]["privateDirtyMem"] = static_cast<double>(sqrt(sumPrivateDirtyMem / mem_nsize));

    (*rc)["std-deviation"]["sharedMem"] = static_cast<double>(sqrt(sumSharedMem / mem_nsize));
    (*rc)["std-deviation"]["sharedCleanMem"] = static_cast<double>(sqrt(sumSharedCleanMem / mem_nsize));
    (*rc)["std-deviation"]["sharedDirtyMem"] = static_cast<double>(sqrt(sumSharedDirtyMem / mem_nsize));

    (*rc)["std-deviation"]["stackSize"] = static_cast<double>(sqrt(sumStackSize / mem_nsize));
    (*rc)["std-deviation"]["stackRss"] = static_cast<double>(sqrt(sumStackRss / mem_nsize));
    (*rc)["std-deviation"]["stackRef"] = static_cast<double>(sqrt(sumStackRef / mem_nsize));
    (*rc)["std-deviation"]["stackClean"] = static_cast<double>(sqrt(sumStackClean / mem_nsize));
    (*rc)["std-deviation"]["stackDirty"] = static_cast<double>(sqrt(sumStackDirty / mem_nsize));

    (*rc)["std-deviation"]["heapSize"] = static_cast<double>(sqrt(sumHeapSize / mem_nsize));
    (*rc)["std-deviation"]["heapRss"] = static_cast<double>(sqrt(sumHeapRss / mem_nsize));
    (*rc)["std-deviation"]["heapRef"] = static_cast<double>(sqrt(sumHeapRef / mem_nsize));
    (*rc)["std-deviation"]["heapClean"] = static_cast<double>(sqrt(sumHeapClean / mem_nsize));
    (*rc)["std-deviation"]["heapDirty"] = static_cast<double>(sqrt(sumHeapDirty / mem_nsize));

    (*rc)["std-deviation"]["vmData"] = static_cast<double>(sqrt(sumVmData / mem_nsize));
    (*rc)["std-deviation"]["vmExe"] = static_cast<double>(sqrt(sumVmExe / mem_nsize));
    (*rc)["std-deviation"]["vmLib"] = static_cast<double>(sqrt(sumVmLib / mem_nsize));
    (*rc)["std-deviation"]["vmPTE"] = static_cast<double>(sqrt(sumVmPTE  / mem_nsize));

    (*rc)["std-deviation"]["pagefaults"] = static_cast<double>(sqrt(sumPagefaults / mem_nsize));
}
