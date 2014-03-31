#include "performer/data_collection/datacollector.h"
#include "performer/config/configfile.h"
#include "performer/pfactory.h"
#include <iostream>

using namespace std;

/**
*Constructor takes a configfile as its parameter which it uses to determine whether to load a file
*or to create a new file
*/
DataCollector::DataCollector(ConfigFile *_cf):cf(_cf)
{
    if(cf->isLoadFile()){
        rxml = new ResultXML(cf->getFileLocation());
        cf->setSourceName(rxml->getSourceName());
    }
    else{
        rxml = new ResultXML(cf->getFileLocation(), cf->getSource());
    }

    //get a platform specific timers and memory profilers from the given factory
    PerformerFactory *pf = getPerfFactory();
    dtimer = pf->createTimer();
    mprof = pf->createMemProfiler();

    //set the rxml pointer in config file
    cf->setRxml(rxml);

    delete pf;
}

/**
*Destructor
*/
DataCollector::~DataCollector()
{
    delete rxml;
    delete dtimer;
    delete mprof;

    //unset the rxml pointer in config file
    cf->setRxml(NULL);
}

/**
*Specifies the start point to measure i.e. when to take the first measurement
*/
void DataCollector::startSection(const char *_section)
{
    dtimer->setUseOffset(cf->getUseTimerOffset());
    section = _section;
    dtimer->startTimer();
    mprof->poll();
    minfo = mprof->getMemInfo();
}

/**
*specifies where to stop the measurement, or rather the 2nd measurement and calculate the difference from the first
*/
ResultInfo DataCollector::stopSection()
{
    dtimer->stopTimer();
    mprof->poll();
    MemInfo tmpMi = mprof->getMemInfo();
    minfo = tmpMi - minfo;

    //add the results to the resultxml object
    rxml->addSpeedResult(dtimer->getResult(), section.c_str());
    rxml->addMemResult(minfo, section.c_str());

    //autosave if it is enabled
    if(cf->isAutoSave()){
        rxml->save();
    }

    //store the speed and memory results in a ResultInfo structure and return it
    ResultInfo ri;
    ri.si = dtimer->getResult();
    ri.mi = minfo;

    return ri;
}


/**
*takes a memory snapshot of the process and returns the result, by default it will not save the result
*/
MemInfo DataCollector::memPoll(bool saveResult, const char* sect)
{
    mprof->poll();
    if(saveResult){
        rxml->addMemResult(mprof->getMemInfo(), sect);
    }

    //autosave if it is enabled
    if(cf->isAutoSave()){
        rxml->save();
    }

    return mprof->getMemInfo();
}

/**
*get all the saved speed results, which is retrieved from the resultxml object, you can pass a pointer to be filled in or simply take
*the return value
*/
void DataCollector::getSpeedResult(speed_map *sm)
{
    rxml->getSpeedResult(sm);
}

/**
*get all the saved memory results, which is retireved from the resultxml object, you can pass a pointer to be filled in or simply take
*the return value
*/
void DataCollector::getMemResult(mem_map *mm)
{
    rxml->getMemResult(mm);
}

/**
*print all the speed and memory results to the standard output
*/
void DataCollector::printResults()
{
    speed_map *sm;
    mem_map *mm;
    getSpeedResult(sm);
    getMemResult(mm);

    cout << *sm;
    cout << endl;
    cout << *mm;
}

/**
*get the xml document
*/
ResultXML* DataCollector::getResultXML()
{
    //autosave if it is enabled
    if(cf->isAutoSave()){
        rxml->save();
    }

    return rxml;
}

/**
*add a MemInfo structure to the resultxml object managed by this datacollector
*/
void DataCollector::addMemInfo(MemInfo &mi, const char *sect)
{
    rxml->addMemResult(mi, sect);

    //autosave if it is enabled
    if(cf->isAutoSave()){
        rxml->save();
    }
}

/**
*add a SpeedInfo structure to the resultxml object managed by this datacollector
*/
void DataCollector::addSpeedInfo(SpeedInfo &si, const char *sect)
{
    rxml->addSpeedResult(si, sect);

    //autosave if it is enabled
    if(cf->isAutoSave()){
        rxml->save();
    }
}
