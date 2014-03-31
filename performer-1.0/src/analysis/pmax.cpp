#include "performer/analysis/pmax.h"

Pmax::Pmax(result_category *rc):PerformerFunctor("max", rc)
{
    //ctor
}

Pmax::~Pmax()
{
    //dtor
}

/**
*find the max values for speed results
*/
void Pmax::operator()(const SpeedInfo &si)
{
    (*rc)["max"]["wallTime"] = (*rc)["max"]["wallTime"] < si.wallTime ? si.wallTime : (*rc)["max"]["wallTime"];
    (*rc)["max"]["cpuTime"] = (*rc)["max"]["cpuTime"] < si.wallTime ? si.wallTime : (*rc)["max"]["cpuTime"];
    (*rc)["max"]["usrTime"] = (*rc)["max"]["usrTime"] < si.wallTime ? si.wallTime : (*rc)["max"]["usrTime"];
    (*rc)["max"]["sysTime"] = (*rc)["max"]["sysTime"] < si.wallTime ? si.wallTime : (*rc)["max"]["sysTime"];
}

/**
*find max values for memory results
*/
void Pmax::operator()(const MemInfo &mi)
{
    (*rc)["max"]["cleanMem"] = (*rc)["max"]["cleanMem"] < mi.cleanMem ? mi.cleanMem : (*rc)["max"]["cleanMem"];
    (*rc)["max"]["dirtyMem"] = (*rc)["max"]["dirtyMem"] < mi.dirtyMem ? mi.dirtyMem : (*rc)["max"]["dirtyMem"];
    (*rc)["max"]["heapClean"] = (*rc)["max"]["heapClean"] < mi.heapClean ? mi.heapClean : (*rc)["max"]["heapClean"];
    (*rc)["max"]["heapDirty"] = (*rc)["max"]["heapDirty"] < mi.heapDirty ? mi.heapDirty : (*rc)["max"]["heapDirty"];

    (*rc)["max"]["heapRef"] = (*rc)["max"]["heapRef"] < mi.heapRef ? mi.heapRef : (*rc)["max"]["heapRef"];
    (*rc)["max"]["heapRss"] = (*rc)["max"]["heapRss"] < mi.heapRss ? mi.heapRss : (*rc)["max"]["heapRss"];
    (*rc)["max"]["heapSize"] = (*rc)["max"]["heapSize"] < mi.heapSize ? mi.heapSize : (*rc)["max"]["heapSize"];

    (*rc)["max"]["pagefaults"] = (*rc)["max"]["pagefaults"] < mi.pagefaults ? mi.pagefaults : (*rc)["max"]["pagefaults"];
    (*rc)["max"]["privateCleanMem"] = (*rc)["max"]["privateCleanMem"] < mi.privateCleanMem ? mi.privateCleanMem : (*rc)["max"]["privateCleanMem"];
    (*rc)["max"]["privateDirtyMem"] = (*rc)["max"]["privateDirtyMem"] < mi.privateDirtyMem ? mi.privateDirtyMem : (*rc)["max"]["privateDirtyMem"];
    (*rc)["max"]["privateMem"] = (*rc)["max"]["privateMem"] < mi.privateMem ? mi.privateMem : (*rc)["max"]["privateMem"];

    (*rc)["max"]["refMem"] = (*rc)["max"]["refMem"] < mi.refMem ? mi.refMem : (*rc)["max"]["refMem"];
    (*rc)["max"]["rsSize"] = (*rc)["max"]["rsSize"] < mi.rsSize ? mi.rsSize : (*rc)["max"]["rsSize"];
    (*rc)["max"]["sharedCleanMem"] = (*rc)["max"]["sharedCleanMem"] < mi.sharedCleanMem ? mi.sharedCleanMem : (*rc)["max"]["sharedCleanMem"];
    (*rc)["max"]["sharedDirtyMem"] = (*rc)["max"]["sharedDirtyMem"] < mi.sharedDirtyMem ? mi.sharedDirtyMem : (*rc)["max"]["sharedDirtyMem"];

    (*rc)["max"]["sharedMem"] = (*rc)["max"]["sharedMem"] < mi.sharedMem ? mi.sharedMem : (*rc)["max"]["sharedMem"];
    (*rc)["max"]["stackClean"] = (*rc)["max"]["stackClean"] < mi.stackClean ? mi.stackClean : (*rc)["max"]["stackClean"];
    (*rc)["max"]["stackDirty"] = (*rc)["max"]["stackDirty"] < mi.stackDirty ? mi.stackDirty : (*rc)["max"]["stackDirty"];
    (*rc)["max"]["stackRef"] = (*rc)["max"]["stackRef"] < mi.stackRef ? mi.stackRef : (*rc)["max"]["stackRef"];

    (*rc)["max"]["stackRss"] = (*rc)["max"]["stackRss"] < mi.stackRss ? mi.stackRss : (*rc)["max"]["stackRss"];
    (*rc)["max"]["stackSize"] = (*rc)["max"]["stackSize"] < mi.stackSize ? mi.stackSize : (*rc)["max"]["stackSize"];
    (*rc)["max"]["swapMem"] = (*rc)["max"]["swapMem"] < mi.swapMem ? mi.swapMem : (*rc)["max"]["swapMem"];
    (*rc)["max"]["vmData"] = (*rc)["max"]["vmData"] < mi.vmData ? mi.vmData : (*rc)["max"]["vmData"];

    (*rc)["max"]["vmExe"] = (*rc)["max"]["vmExe"] < mi.vmExe ? mi.vmExe : (*rc)["max"]["vmExe"];
    (*rc)["max"]["vmLib"] = (*rc)["max"]["vmLib"] < mi.vmLib ? mi.vmLib : (*rc)["max"]["vmLib"];
    (*rc)["max"]["vmPTE"] = (*rc)["max"]["vmPTE"] < mi.vmPTE ? mi.vmPTE : (*rc)["max"]["vmPTE"];
    (*rc)["max"]["vsSize"] = (*rc)["max"]["vsSize"] < mi.vsSize ? mi.vsSize : (*rc)["max"]["vsSize"];
}
