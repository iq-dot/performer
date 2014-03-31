#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

#include "performer/config/configfile.h"
#include "performer/data_collection/resultxml.h"
#include "performer/data_collection/pstructs.h"
#include "performer/data_collection/timer.h"
#include "performer/data_collection/memprof.h"

class DataCollector
{
    public:
        DataCollector(ConfigFile *_cf);
        ~DataCollector();

        //these methods are used to define a section to measure which can be a section of code or a method, it is required to give this
        //section a name for identification
        void startSection(const char* sect="undefined");
        ResultInfo stopSection();

        //takes a memory snapshot of the process and returns the result, by default it will not save the result
        MemInfo memPoll(bool saveResult = false, const char* sect="undefined");

        //methods used to retrieve the measured results, speed and memory results are stored in speed_map and memory_map structures respectively
        //they can either take a pointer or return a pointer, either way it give back the result structures
        void getSpeedResult(speed_map *sm);
        void getMemResult(mem_map *mm);

        //a convinient way to print results to the standard output
        void printResults();

        //get the xml document
        ResultXML* getResultXML();

        //if users have made their own measurements they can add it to the resultxml object managed by the datacollector
        void addMemInfo(MemInfo &mi, const char *sect="undefined");
        void addSpeedInfo(SpeedInfo &si, const char *sect="undefined");

    private:
        //private fields to store, the config file reference, a resultxml file for storing results and the individual timers and memory profilers
        ConfigFile *cf;
        ResultXML *rxml;
        std::string section;

        Timer *dtimer;
        MemProfiler *mprof;
        MemInfo minfo;

        //disallow copy constructor and assignment
        DataCollector(const DataCollector& other);
        DataCollector& operator=(const DataCollector& other);
};

#endif // DATACOLLECTOR_H
