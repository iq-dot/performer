#include "performer/data_collection/pstructs.h"
#include <iterator>
#include <algorithm>

#define PSTRUCT_EXPORT

using namespace std;

//output stream operator for speedInfo struct
ostream& operator<<(ostream &st, const SpeedInfo &si)
{
    st << "wallTime: " << si.wallTime << endl
        << "cpuTime: " << si.cpuTime << endl
        << "usrTime: " << si.usrTime << endl
        << "sysTime: " << si.sysTime << endl;

    return st;
}

//output stream operator for MemInfo struct
ostream& operator<<(ostream &st, const MemInfo &mi)
{
    st << "Virtual Memory: " << mi.vsSize << endl;
    st << "Resident Memory: " << mi.rsSize << endl;
    st << "Referenced Memory: " << mi.refMem << endl;
    st << "Swap Memory: " << mi.swapMem << endl;

    st << endl;

    st << "Clean Memory: " << mi.cleanMem << endl;
    st << "Dirty Memory: " << mi.dirtyMem << endl;

    st << endl;

    st << "Private Memory: " << mi.privateMem << endl;
    st << "Private Clean Memory: " << mi.privateCleanMem << endl;
    st << "Private Dirty Memory: " << mi.privateDirtyMem << endl;

    st << endl;

    st << "Shared Memory: " << mi.sharedMem << endl;
    st << "Shared Clean Memory: " << mi.sharedCleanMem << endl;
    st << "Shared Dirty Memory: " << mi.sharedDirtyMem << endl;

    st << endl;

    st << "Stack Virtual: " << mi.stackSize << endl;
    st << "Stack Resident: " << mi.stackRss << endl;
    st << "Stack Referenced: " << mi.stackRef << endl;
    st << "Stack Clean: " << mi.stackClean << endl;
    st << "Stack Dirty: " << mi.stackDirty << endl;

    st << endl;

    st << "Heap Virtual: " << mi.heapSize << endl;
    st << "Heap Resident: " << mi.heapRss << endl;
    st << "Heap Referenced: " << mi.heapRef << endl;
    st << "Heap Clean: " << mi.heapClean << endl;
    st << "Heap Dirty: " << mi.heapDirty << endl;

    st << endl;

    st << "Virtual Data Memory: " << mi.vmData << endl;
    st << "Virtual Executable Memory: " << mi.vmExe << endl;
    st << "Virtual Library Memory: " << mi.vmLib << endl;
    st << "Virtual Page Table Entry Memory: " << mi.vmPTE << endl;

    st << endl;

    st << "No of Pagefaults: " << mi.pagefaults << endl;

    return st;
}

//print a ResultInfo structure
ostream& operator<<(ostream &st, const ResultInfo &ri)
{
    st << ri.si;
    st << endl;
    st << ri.mi;

    return st;
}

//stream operator for the analyzed_result data type
ostream& operator<<(ostream &st, const analyzed_result &ar)
{
    st << "******************** Result of Analysis ********************" << endl;

    for(analyzed_result::const_iterator it = ar.begin(); it != ar.end(); it++){
        st << endl << "result-type = " << it->first << ":" << endl;

        for(analyzed_result::mapped_type::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
            st << endl << "\tsection-name = " << it2->first << ":" << endl;

            for(result_category::const_iterator it3 = it2->second.begin(); it3 != it2->second.end(); it3++){
                st << endl <<"\t\tcategory = " << it3->first << ":" << endl;

                for(result_category::mapped_type::const_iterator it4 = it3->second.begin(); it4 != it3->second.end(); it4++){
                    st << "\t\t\t" << it4->first << ": " << it4->second << endl;
                }
            }
        }

    }
    st << endl << "****************** End of Analysis Result ******************" << endl;
    return st;
}

//stream operator for printing ustring_set data type
ostream& operator<<(ostream &st, const ustring_set& us)
{
    st << "************** Section List **************" << endl << endl;
    for(ustring_set::const_iterator it = us.begin(); it != us.end(); it++){
        st << *it << endl;
    }
    st << endl << "*********** End of Section List **********" << endl;

    return st;
}

//stream operator for the speed_map data type
ostream& operator<<(ostream &st, const speed_map &sm)
{
    st << "******************* Speed Results *******************" << endl;

    for(speed_map::const_iterator it = sm.begin(); it != sm.end(); it++){
        st << endl << "##### section-name = " << it->first << " #####" << endl;

        for(speed_map::mapped_type::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
            st << endl << *it2 << endl;
            st << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        }
    }
    st << "****************** End of Results ******************" << endl;

    return st;
}

//stream operator for the mem_map data type
ostream& operator<<(ostream &st, const mem_map &mm)
{
    st << "******************* Memory Results ******************" << endl;

    for(mem_map::const_iterator it = mm.begin(); it != mm.end(); it++){
        st << endl << "##### section-name = " << it->first << " #####" << endl;

        for(mem_map::mapped_type::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
            st << endl << *it2 << endl;
            st << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        }
    }
    st << "****************** End of Results ******************" << endl;

    return st;
}

/**
*Add two SpeedInfo structures
*/
SpeedInfo operator+(SpeedInfo &si, SpeedInfo &si2)
{
    SpeedInfo result;
    result.cpuTime = si.cpuTime + si2.cpuTime;
    result.wallTime = si.wallTime + si2.wallTime;
    result.usrTime = si.usrTime + si2.usrTime;
    result.sysTime = si.sysTime + si2.sysTime;

    return result;
}

/**
*Add and assing two SpeedInfo structures
*/
SpeedInfo& operator+=(SpeedInfo &si, SpeedInfo &si2)
{
    si.cpuTime = si.cpuTime + si2.cpuTime;
    si.wallTime = si.wallTime + si2.wallTime;
    si.usrTime = si.usrTime + si2.usrTime;
    si.sysTime = si.sysTime + si2.sysTime;

    return si;
}

/**
*Minus two SpeedInfo structures
*/
SpeedInfo operator-(SpeedInfo &si, SpeedInfo &si2)
{
    SpeedInfo result;
    result.cpuTime = si.cpuTime- si2.cpuTime;
    result.wallTime = si.wallTime - si2.wallTime;
    result.usrTime = si.usrTime - si2.usrTime;
    result.sysTime = si.sysTime - si2.sysTime;

    return result;
}

/**
*Minus and assign two SpeedInfo structures
*/
SpeedInfo& operator-=(SpeedInfo &si, SpeedInfo &si2)
{
    si.cpuTime = si.cpuTime - si2.cpuTime;
    si.wallTime = si.wallTime - si2.wallTime;
    si.usrTime = si.usrTime - si2.usrTime;
    si.sysTime = si.sysTime - si2.sysTime;

    return si;
}

/**
*Add two MemInfo structures
*/
MemInfo operator+(MemInfo &mi, MemInfo &mi2)
{
    MemInfo result;
    result.cleanMem = mi.cleanMem + mi2.cleanMem;
    result.dirtyMem = mi.dirtyMem + mi2.dirtyMem;
    result.heapClean = mi.heapClean + mi2.heapClean;
    result.heapDirty = mi.heapDirty + mi2.heapDirty;
    result.heapRef = mi.heapRef + mi2.heapRef;
    result.heapRss = mi.heapRss + mi2.heapRss;
    result.heapSize = mi.heapSize + mi2.heapSize;
    result.pagefaults = mi.pagefaults + mi2.pagefaults;
    result.privateCleanMem = mi.privateCleanMem + mi2.privateCleanMem;
    result.privateDirtyMem = mi.privateDirtyMem + mi2.privateDirtyMem;
    result.privateMem = mi.privateMem + mi2.privateMem;
    result.refMem = mi.refMem + mi2.refMem;
    result.rsSize = mi.rsSize + mi2.rsSize;
    result.sharedCleanMem = mi.sharedCleanMem + mi2.sharedCleanMem;
    result.sharedDirtyMem = mi.sharedDirtyMem + mi2.sharedDirtyMem;
    result.sharedMem = mi.sharedMem + mi2.sharedMem;
    result.stackClean = mi.stackClean + mi2.stackClean;
    result.stackDirty = mi.stackDirty + mi2.stackDirty;
    result.stackRef = mi.stackRef + mi2.stackRef;
    result.stackRss = mi.stackRss + mi2.stackRss;
    result.stackSize = mi.stackSize + mi2.stackSize;
    result.swapMem = mi.swapMem + mi2.swapMem;
    result.vmData = mi.vmData + mi2.vmData;
    result.vmExe = mi.vmExe + mi2.vmExe;
    result.vmLib = mi.vmLib + mi2.vmLib;
    result.vmPTE = mi.vmPTE + mi2.vmPTE;
    result.vsSize = mi.vsSize + mi2.vsSize;

    return result;
}


/**
*Add and assign two MemInfo structures
*/
MemInfo& operator+=(MemInfo &mi, MemInfo &mi2)
{
    mi.cleanMem = mi.cleanMem + mi2.cleanMem;
    mi.dirtyMem = mi.dirtyMem + mi2.dirtyMem;
    mi.heapClean = mi.heapClean + mi2.heapClean;
    mi.heapDirty = mi.heapDirty + mi2.heapDirty;
    mi.heapRef = mi.heapRef + mi2.heapRef;
    mi.heapRss = mi.heapRss + mi2.heapRss;
    mi.heapSize = mi.heapSize + mi2.heapSize;
    mi.pagefaults = mi.pagefaults + mi2.pagefaults;
    mi.privateCleanMem = mi.privateCleanMem + mi2.privateCleanMem;
    mi.privateDirtyMem = mi.privateDirtyMem + mi2.privateDirtyMem;
    mi.privateMem = mi.privateMem + mi2.privateMem;
    mi.refMem = mi.refMem + mi2.refMem;
    mi.rsSize = mi.rsSize + mi2.rsSize;
    mi.sharedCleanMem = mi.sharedCleanMem + mi2.sharedCleanMem;
    mi.sharedDirtyMem = mi.sharedDirtyMem + mi2.sharedDirtyMem;
    mi.sharedMem = mi.sharedMem + mi2.sharedMem;
    mi.stackClean = mi.stackClean + mi2.stackClean;
    mi.stackDirty = mi.stackDirty + mi2.stackDirty;
    mi.stackRef = mi.stackRef + mi2.stackRef;
    mi.stackRss = mi.stackRss + mi2.stackRss;
    mi.stackSize = mi.stackSize + mi2.stackSize;
    mi.swapMem = mi.swapMem + mi2.swapMem;
    mi.vmData = mi.vmData + mi2.vmData;
    mi.vmExe = mi.vmExe + mi2.vmExe;
    mi.vmLib = mi.vmLib + mi2.vmLib;
    mi.vmPTE = mi.vmPTE + mi2.vmPTE;
    mi.vsSize = mi.vsSize + mi2.vsSize;

    return mi;
}

/**
*Minus two MemInfo structures
*/
MemInfo operator-(MemInfo &mi, MemInfo &mi2)
{
    MemInfo result;
    result.cleanMem = mi.cleanMem - mi2.cleanMem;
    result.dirtyMem = mi.dirtyMem - mi2.dirtyMem;
    result.heapClean = mi.heapClean - mi2.heapClean;
    result.heapDirty = mi.heapDirty - mi2.heapDirty;
    result.heapRef = mi.heapRef - mi2.heapRef;
    result.heapRss = mi.heapRss - mi2.heapRss;
    result.heapSize = mi.heapSize - mi2.heapSize;
    result.pagefaults = mi.pagefaults - mi2.pagefaults;
    result.privateCleanMem = mi.privateCleanMem - mi2.privateCleanMem;
    result.privateDirtyMem = mi.privateDirtyMem - mi2.privateDirtyMem;
    result.privateMem = mi.privateMem - mi2.privateMem;
    result.refMem = mi.refMem - mi2.refMem;
    result.rsSize = mi.rsSize - mi2.rsSize;
    result.sharedCleanMem = mi.sharedCleanMem - mi2.sharedCleanMem;
    result.sharedDirtyMem = mi.sharedDirtyMem - mi2.sharedDirtyMem;
    result.sharedMem = mi.sharedMem - mi2.sharedMem;
    result.stackClean = mi.stackClean - mi2.stackClean;
    result.stackDirty = mi.stackDirty - mi2.stackDirty;
    result.stackRef = mi.stackRef - mi2.stackRef;
    result.stackRss = mi.stackRss - mi2.stackRss;
    result.stackSize = mi.stackSize - mi2.stackSize;
    result.swapMem = mi.swapMem - mi2.swapMem;
    result.vmData = mi.vmData - mi2.vmData;
    result.vmExe = mi.vmExe - mi2.vmExe;
    result.vmLib = mi.vmLib - mi2.vmLib;
    result.vmPTE = mi.vmPTE - mi2.vmPTE;
    result.vsSize = mi.vsSize - mi2.vsSize;

    return result;
}

/**
*Minus and assign two MemInfo structures
*/
MemInfo& operator-=(MemInfo &mi, MemInfo &mi2)
{
    mi.cleanMem = mi.cleanMem - mi2.cleanMem;
    mi.dirtyMem = mi.dirtyMem - mi2.dirtyMem;
    mi.heapClean = mi.heapClean - mi2.heapClean;
    mi.heapDirty = mi.heapDirty - mi2.heapDirty;
    mi.heapRef = mi.heapRef - mi2.heapRef;
    mi.heapRss = mi.heapRss - mi2.heapRss;
    mi.heapSize = mi.heapSize - mi2.heapSize;
    mi.pagefaults = mi.pagefaults - mi2.pagefaults;
    mi.privateCleanMem = mi.privateCleanMem - mi2.privateCleanMem;
    mi.privateDirtyMem = mi.privateDirtyMem - mi2.privateDirtyMem;
    mi.privateMem = mi.privateMem - mi2.privateMem;
    mi.refMem = mi.refMem - mi2.refMem;
    mi.rsSize = mi.rsSize - mi2.rsSize;
    mi.sharedCleanMem = mi.sharedCleanMem - mi2.sharedCleanMem;
    mi.sharedDirtyMem = mi.sharedDirtyMem - mi2.sharedDirtyMem;
    mi.sharedMem = mi.sharedMem - mi2.sharedMem;
    mi.stackClean = mi.stackClean - mi2.stackClean;
    mi.stackDirty = mi.stackDirty - mi2.stackDirty;
    mi.stackRef = mi.stackRef - mi2.stackRef;
    mi.stackRss = mi.stackRss - mi2.stackRss;
    mi.stackSize = mi.stackSize - mi2.stackSize;
    mi.swapMem = mi.swapMem - mi2.swapMem;
    mi.vmData = mi.vmData - mi2.vmData;
    mi.vmExe = mi.vmExe - mi2.vmExe;
    mi.vmLib = mi.vmLib - mi2.vmLib;
    mi.vmPTE = mi.vmPTE - mi2.vmPTE;
    mi.vsSize = mi.vsSize - mi2.vsSize;

    return mi;
}
