#include "performer/analysis/pmin.h"

Pmin::Pmin(result_category *rc):PerformerFunctor("min", rc), spdFirstCall(true), memFirstCall(true)
{
    //ctor
}

Pmin::~Pmin()
{
    //dtor
}

/**
*test for minimum values in the speed result section and update the result_category as neccessary
*/
void Pmin::operator()(const SpeedInfo &si)
{
    //if this is the first call, then set the min values as the current SpeedInfo structure
    if(spdFirstCall){
        (*rc)["min"]["wallTime"] = si.wallTime;
        (*rc)["min"]["cpuTime"] = si.wallTime;
        (*rc)["min"]["usrTime"] = si.wallTime;
        (*rc)["min"]["sysTime"] = si.wallTime;

        spdFirstCall = false;
    }

   (*rc)["min"]["wallTime"] = (*rc)["min"]["wallTime"] > si.wallTime ? si.wallTime : (*rc)["min"]["wallTime"];
   (*rc)["min"]["cpuTime"] = (*rc)["min"]["cpuTime"] > si.wallTime ? si.wallTime : (*rc)["min"]["cpuTime"];
   (*rc)["min"]["usrTime"] = (*rc)["min"]["usrTime"] > si.wallTime ? si.wallTime : (*rc)["min"]["usrTime"];
   (*rc)["min"]["sysTime"] = (*rc)["min"]["sysTime"] > si.wallTime ? si.wallTime : (*rc)["min"]["sysTime"];
}

/**
*test for minimum values in the memory result section and update the result_category as neccessary
*/
void Pmin::operator()(const MemInfo &mi)
{
    //if this is the first call, then set the min values as the current MemInfo structure
    if(memFirstCall){

        (*rc)["min"]["cleanMem"] = mi.cleanMem;
        (*rc)["min"]["dirtyMem"] = mi.dirtyMem;
        (*rc)["min"]["heapClean"] = mi.heapDirty;

        (*rc)["min"]["heapRef"] = mi.heapRef;
        (*rc)["min"]["heapRss"] = mi.heapRss;
        (*rc)["min"]["heapSize"] = mi.heapSize;

        (*rc)["min"]["pagefaults"] = mi.pagefaults;
        (*rc)["min"]["privateCleanMem"] = mi.privateCleanMem;
        (*rc)["min"]["privateDirtyMem"] = mi.privateDirtyMem;
        (*rc)["min"]["privateMem"] = mi.privateMem;

        (*rc)["min"]["refMem"] = mi.refMem;
        (*rc)["min"]["rsSize"] = mi.rsSize;
        (*rc)["min"]["sharedCleanMem"] = mi.sharedCleanMem;
        (*rc)["min"]["sharedDirtyMem"] = mi.sharedDirtyMem;

        (*rc)["min"]["sharedMem"] = mi.sharedMem;
        (*rc)["min"]["stackClean"] = mi.stackClean;
        (*rc)["min"]["stackDirty"] = mi.stackDirty;
        (*rc)["min"]["stackRef"] = mi.stackRef;

        (*rc)["min"]["stackRss"] = mi.stackRss;
        (*rc)["min"]["stackSize"] = mi.stackSize;
        (*rc)["min"]["swapMem"] = mi.swapMem;
        (*rc)["min"]["vmData"] = mi.vmData;

        (*rc)["min"]["vmExe"] = mi.vmExe;
        (*rc)["min"]["vmLib"] = mi.vmLib;
        (*rc)["min"]["vmPTE"] = mi.vmPTE;
        (*rc)["min"]["vsSize"] = mi.vsSize;

        memFirstCall = false;
    }

    (*rc)["min"]["cleanMem"] = (*rc)["min"]["cleanMem"] > mi.cleanMem ? mi.cleanMem : (*rc)["min"]["cleanMem"];
    (*rc)["min"]["dirtyMem"] = (*rc)["min"]["dirtyMem"] > mi.dirtyMem ? mi.dirtyMem : (*rc)["min"]["dirtyMem"];
    (*rc)["min"]["heapClean"] = (*rc)["min"]["heapClean"] > mi.heapClean ? mi.heapClean : (*rc)["min"]["heapClean"];
    (*rc)["min"]["heapDirty"] = (*rc)["min"]["heapDirty"] > mi.heapDirty ? mi.heapDirty : (*rc)["min"]["heapDirty"];

    (*rc)["min"]["heapRef"] = (*rc)["min"]["heapRef"] > mi.heapRef ? mi.heapRef : (*rc)["min"]["heapRef"];
    (*rc)["min"]["heapRss"] = (*rc)["min"]["heapRss"] > mi.heapRss ? mi.heapRss : (*rc)["min"]["heapRss"];
    (*rc)["min"]["heapSize"] = (*rc)["min"]["heapSize"] > mi.heapSize ? mi.heapSize : (*rc)["min"]["heapSize"];

    (*rc)["min"]["pagefaults"] = (*rc)["min"]["pagefaults"] > mi.pagefaults ? mi.pagefaults : (*rc)["min"]["pagefaults"];
    (*rc)["min"]["privateCleanMem"] = (*rc)["min"]["privateCleanMem"] > mi.privateCleanMem ? mi.privateCleanMem : (*rc)["min"]["privateCleanMem"];
    (*rc)["min"]["privateDirtyMem"] = (*rc)["min"]["privateDirtyMem"] > mi.privateDirtyMem ? mi.privateDirtyMem : (*rc)["min"]["privateDirtyMem"];
    (*rc)["min"]["privateMem"] = (*rc)["min"]["privateMem"] > mi.privateMem ? mi.privateMem : (*rc)["min"]["privateMem"];

    (*rc)["min"]["refMem"] = (*rc)["min"]["refMem"] > mi.refMem ? mi.refMem : (*rc)["min"]["refMem"];
    (*rc)["min"]["rsSize"] = (*rc)["min"]["rsSize"] > mi.rsSize ? mi.rsSize : (*rc)["min"]["rsSize"];
    (*rc)["min"]["sharedCleanMem"] = (*rc)["min"]["sharedCleanMem"] > mi.sharedCleanMem ? mi.sharedCleanMem : (*rc)["min"]["sharedCleanMem"];
    (*rc)["min"]["sharedDirtyMem"] = (*rc)["min"]["sharedDirtyMem"] > mi.sharedDirtyMem ? mi.sharedDirtyMem : (*rc)["min"]["sharedDirtyMem"];

    (*rc)["min"]["sharedMem"] = (*rc)["min"]["sharedMem"] > mi.sharedMem ? mi.sharedMem : (*rc)["min"]["sharedMem"];
    (*rc)["min"]["stackClean"] = (*rc)["min"]["stackClean"] > mi.stackClean ? mi.stackClean : (*rc)["min"]["stackClean"];
    (*rc)["min"]["stackDirty"] = (*rc)["min"]["stackDirty"] > mi.stackDirty ? mi.stackDirty : (*rc)["min"]["stackDirty"];
    (*rc)["min"]["stackRef"] = (*rc)["min"]["stackRef"] > mi.stackRef ? mi.stackRef : (*rc)["min"]["stackRef"];

    (*rc)["min"]["stackRss"] = (*rc)["min"]["stackRss"] > mi.stackRss ? mi.stackRss : (*rc)["min"]["stackRss"];
    (*rc)["min"]["stackSize"] = (*rc)["min"]["stackSize"] > mi.stackSize ? mi.stackSize : (*rc)["min"]["stackSize"];
    (*rc)["min"]["swapMem"] = (*rc)["min"]["swapMem"] > mi.swapMem ? mi.swapMem : (*rc)["min"]["swapMem"];
    (*rc)["min"]["vmData"] = (*rc)["min"]["vmData"] > mi.vmData ? mi.vmData : (*rc)["min"]["vmData"];

    (*rc)["min"]["vmExe"] = (*rc)["min"]["vmExe"] > mi.vmExe ? mi.vmExe : (*rc)["min"]["vmExe"];
    (*rc)["min"]["vmLib"] = (*rc)["min"]["vmLib"] > mi.vmLib ? mi.vmLib : (*rc)["min"]["vmLib"];
    (*rc)["min"]["vmPTE"] = (*rc)["min"]["vmPTE"] > mi.vmPTE ? mi.vmPTE : (*rc)["min"]["vmPTE"];
    (*rc)["min"]["vsSize"] = (*rc)["min"]["vsSize"] > mi.vsSize ? mi.vsSize : (*rc)["min"]["vsSize"];
}
