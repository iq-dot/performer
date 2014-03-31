#ifndef PERF_ANALYZER_H
#define PERF_ANALYZER_H

#include "performer/config/configfile.h"
#include "performer/data_collection/pstructs.h"

class Analyzer
{
    public:
        //the constructors can take any combination of the speed and memory results to process
        Analyzer(ConfigFile*, const speed_map&, const mem_map&);
        Analyzer(ConfigFile*, const speed_map&);
        Analyzer(ConfigFile*, const mem_map&);
        virtual ~Analyzer();

        //the functions that are used by the constructors, users can directly call them to re-process the values
        //with the given speed/memory results and config file
        void analyzeSpeed(ConfigFile*, const speed_map&);
        void analyzeMemory(ConfigFile*, const mem_map&);

        ustring_set getSectionList() const;
        void printSectionList();

        //provide the option of getting either getting a copy of the result or pointer to the original
        const analyzed_result& getResult() const;
        analyzed_result getResultCopy() const;

    private:
        ustring_set sectionList;
        analyzed_result result;
};

#endif // PERF_ANALYZER_H
