#include "performer/pfactory.h"

#ifdef LINUX
#include "performer/data_collection/linux/linfactory.h"
#else
#ifdef WINDOWS
#include "performer/data_collection/windows/winfactory.h"
#endif
#endif

#define PERFORMER_EXPORT

/**
*@brief Check for Linux or Windows and return the appropriate factory object
*/
PerformerFactory* getPerfFactory()
{
    #ifdef LINUX
        return new LinFactory;
    #else
    #ifdef WINDOWS
        return new WinFactory;
    #endif
    #endif
}

/** @brief Default constructor
  *
  */
 PerformerFactory::PerformerFactory()
{

}

/** @brief Default destructor
  *
  */
 PerformerFactory::~PerformerFactory()
{

}

/** @brief Returns a pointer to a Comparer object
  *
  */
Comparer * PerformerFactory::createComparer(const analyzed_result &ar1, const analyzed_result &ar2)
{
    return new Comparer(ar1, ar2);
}

/** @brief Returns a pointer to a Analyzer object for both speed and memory results
  *
  */
Analyzer * PerformerFactory::createAnalyzer(ConfigFile *cf, const speed_map &sm, const mem_map &mm)
{
    return new Analyzer(cf, sm, mm);
}

/** @brief Returns a pointer to a Analyzer object for speed results
  *
  */
Analyzer* PerformerFactory::createAnalyzer(ConfigFile *cf, const speed_map &sm)
{
    return new Analyzer(cf,sm);
}

/** @brief Returns a pointer to a Analyzer object for memory results
  *
  */
Analyzer* PerformerFactory::createAnalyzer(ConfigFile *cf, const mem_map &mm)
{
    return new Analyzer(cf, mm);
}

/** @brief Returns a pointer to a ResultXML object
  *It will either load or create a xml object from scratch depending on what parameters are given
  */
ResultXML * PerformerFactory::createResultXML(const char *fnameandloc, const char *src)
{
    if(src==0){
        return new ResultXML(fnameandloc);
    }
    else{
        return new ResultXML(fnameandloc, src);
    }
}

/** @brief Returns a pointer to a DataCollector object
  *
  */
DataCollector * PerformerFactory::createDataCollector(ConfigFile *cf)
{
    return new DataCollector(cf);
}

/** @brief Returns a pointer to a ConfigFile object by loading file or by default constructor
  *
  */
ConfigFile * PerformerFactory::createConfigObject(const char *load)
{
    if(load==0){
        return new ConfigFile;
    }
    else{
        return new ConfigFile(load);
    }
}

/** @brief Returns a pointer to a ConfigFile object by specifying to create a new save file
  *
  */
ConfigFile * PerformerFactory::createConfigObject(const char *src, const char *fname, const char *saveloc)
{
    return new ConfigFile(src, fname, saveloc);
}

