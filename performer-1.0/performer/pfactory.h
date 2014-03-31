#ifndef PERFORMFACTORY_H
#define PERFORMFACTORY_H

#include "performer/data_collection/timer.h"
#include "performer/data_collection/memprof.h"
#include "performer/data_collection/resultxml.h"
#include "performer/data_collection/datacollector.h"
#include "performer/analysis/analyzer.h"
#include "performer/analysis/comparer.h"
#include "performer/config/configfile.h"

#ifdef WINDOWS
#   ifdef PERFORMER_EXPORT
#   define WINLIB __declspec(dllexport)
#   else
#   define WINLIB __declspec(dllimport)
#   endif
#   define CALLCONV __stdcall
#else
#  define WINLIB
#  define CALLCONV
#endif

/**
*This is the factory interface used for generating platform specific timer and memory profiler class
*/
class PerformerFactory
{
    public:
        PerformerFactory();
        virtual ~PerformerFactory();

        virtual Timer* createTimer() = 0;
        virtual MemProfiler* createMemProfiler() = 0;

        //creates a config object by loading the specified file, if blank then default constructor will be called
        virtual ConfigFile* createConfigObject(const char *load = 0);

        //creates a config object by specifying to create a new save file for the given source, filename and save location
        virtual ConfigFile* createConfigObject(const char *src, const char *fname, const char *saveloc);

        //create a data collector object using the given config file
        virtual DataCollector* createDataCollector(ConfigFile*);

        //if the second parameter is blank then an xml object will be created by loading the specified file in the first parameter
        //if teh second parameter is given then a new xml object will be created in with the given
        //filename and desitation (combined as the first parameter) for the source specified by the second parameter
        virtual ResultXML* createResultXML(const char *fnameandloc, const char *src=0);

        //create an analyzer component with the given speed and/or memory performance results
        virtual Analyzer* createAnalyzer(ConfigFile*, const speed_map&, const mem_map&);
        virtual Analyzer* createAnalyzer(ConfigFile*, const speed_map&);
        virtual Analyzer* createAnalyzer(ConfigFile*, const mem_map&);

        virtual Comparer* createComparer(const analyzed_result &ar1, const analyzed_result &ar2);
};

/**
*This method generates a platform specific factory object, this should be the first line of code if you using windows
*and will also make the code more portable if your using linux
*/
extern "C" WINLIB PerformerFactory* CALLCONV getPerfFactory();

#endif // PERFORMFACTORY_H
