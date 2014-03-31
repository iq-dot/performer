#include "performer/analysis/paverage.h"
#include <functional>

#include <iostream>

Paverage::Paverage(result_category *rc):PerformerFunctor("average", rc), freq(0)
{
    //ctor
}

Paverage::~Paverage()
{
    //dtor
}

/**
*process the average results for speed results
*/
void Paverage::operator()(const SpeedInfo &si)
{
    int oldFreq = freq;
    freq++;

    (*rc)["average"]["wallTime"] = static_cast<double>((((*rc)["average"]["wallTime"] * oldFreq) + si.wallTime)) / freq;
    (*rc)["average"]["cpuTime"] = static_cast<double>((((*rc)["average"]["cpuTime"] * oldFreq) + si.cpuTime)) / freq;
    (*rc)["average"]["usrTime"] = static_cast<double>((((*rc)["average"]["usrTime"] * oldFreq) + si.usrTime)) / freq;
    (*rc)["average"]["sysTime"] = static_cast<double>((((*rc)["average"]["sysTime"] * oldFreq) + si.sysTime)) / freq;
}

/**
*process averages for memory results
*/
void Paverage::operator()(const MemInfo &mi)
{
    int oldFreq = freq;
    freq++;

    (*rc)["average"]["cleanMem"] = static_cast<double>((((*rc)["average"]["cleanMem"] * oldFreq) + mi.cleanMem)) / freq;
    (*rc)["average"]["dirtyMem"] = static_cast<double>((((*rc)["average"]["dirtyMem"] * oldFreq) + mi.dirtyMem)) / freq;
    (*rc)["average"]["heapClean"] = static_cast<double>((((*rc)["average"]["heapClean"] * oldFreq) + mi.heapClean)) / freq;
    (*rc)["average"]["heapDirty"] = static_cast<double>((((*rc)["average"]["heapDirty"] * oldFreq) + mi.heapDirty)) / freq;

    (*rc)["average"]["heapRef"] = static_cast<double>((((*rc)["average"]["heapRef"] * oldFreq) + mi.heapRef)) / freq;
    (*rc)["average"]["heapRss"] = static_cast<double>((((*rc)["average"]["heapRss"] * oldFreq) + mi.heapRss)) / freq;
    (*rc)["average"]["heapSize"] = static_cast<double>((((*rc)["average"]["heapSize"] * oldFreq) + mi.heapSize)) / freq;

    (*rc)["average"]["pagefaults"] = static_cast<double>((((*rc)["average"]["pagefaults"] * oldFreq) + mi.pagefaults)) / freq;
    (*rc)["average"]["privateCleanMem"] = static_cast<double>((((*rc)["average"]["privateCleanMem"] * oldFreq) + mi.privateCleanMem)) / freq;
    (*rc)["average"]["privateDirtyMem"] = static_cast<double>((((*rc)["average"]["privateDirtyMem"] * oldFreq) + mi.privateDirtyMem)) / freq;
    (*rc)["average"]["privateMem"] = static_cast<double>((((*rc)["average"]["privateMem"] * oldFreq) + mi.privateMem)) / freq;

    (*rc)["average"]["refMem"] = static_cast<double>((((*rc)["average"]["refMem"] * oldFreq) + mi.refMem)) / freq;
    (*rc)["average"]["rsSize"] = static_cast<double>((((*rc)["average"]["rsSize"] * oldFreq) + mi.rsSize)) / freq;
    (*rc)["average"]["sharedCleanMem"] = static_cast<double>((((*rc)["average"]["sharedCleanMem"] * oldFreq) + mi.sharedCleanMem)) / freq;
    (*rc)["average"]["sharedDirtyMem"] = static_cast<double>((((*rc)["average"]["sharedDirtyMem"] * oldFreq) + mi.sharedDirtyMem)) / freq;

    (*rc)["average"]["sharedMem"] = static_cast<double>((((*rc)["average"]["sharedMem"] * oldFreq) + mi.sharedMem)) / freq;
    (*rc)["average"]["stackClean"] = static_cast<double>((((*rc)["average"]["stackClean"] * oldFreq) + mi.stackClean)) / freq;
    (*rc)["average"]["stackDirty"] = static_cast<double>((((*rc)["average"]["stackDirty"] * oldFreq) + mi.stackDirty)) / freq;
    (*rc)["average"]["stackRef"] = static_cast<double>((((*rc)["average"]["stackRef"] * oldFreq) + mi.stackRef)) / freq;

    (*rc)["average"]["stackRss"] = static_cast<double>((((*rc)["average"]["stackRss"] * oldFreq) + mi.stackRss)) / freq;
    (*rc)["average"]["stackSize"] = static_cast<double>((((*rc)["average"]["stackSize"] * oldFreq) + mi.stackSize)) / freq;
    (*rc)["average"]["swapMem"] = static_cast<double>((((*rc)["average"]["swapMem"] * oldFreq) + mi.swapMem)) / freq;
    (*rc)["average"]["vmData"] = static_cast<double>((((*rc)["average"]["vmData"] * oldFreq) + mi.vmData)) / freq;

    (*rc)["average"]["vmExe"] = static_cast<double>((((*rc)["average"]["vmExe"] * oldFreq) + mi.vmExe)) / freq;
    (*rc)["average"]["vmLib"] = static_cast<double>((((*rc)["average"]["vmLib"] * oldFreq) + mi.vmLib)) / freq;
    (*rc)["average"]["vmPTE"] = static_cast<double>((((*rc)["average"]["vmPTE"] * oldFreq) + mi.vmPTE)) / freq;
    (*rc)["average"]["vsSize"] = static_cast<double>((((*rc)["average"]["vsSize"] * oldFreq) + mi.vsSize)) / freq;
}

