#include "performer/analysis/analyzer.h"

#include <algorithm>
#include <performer/analysis/paverage.h>
#include <performer/analysis/pmin.h>
#include <performer/analysis/pmax.h>
#include <performer/analysis/pstddeviation.h>

using namespace std;

/**
*These are helper objects used to call the appropriate operator overloading functions
*They are needed due to a limitation with the current C++ standard regarding bind functions
*and reference parameters. They are mainly used for supporting user created PerformerFunctors
*there are not made available to the user and used internally.
*/
struct spdFunc{
    PerformerFunctor* pf;
    spdFunc(PerformerFunctor* _pf) : pf(_pf) {}

    void operator()(const SpeedInfo &si){
        pf->operator()(si);
    }
};

/**
*Helper for calling memory result operator
*/
struct memFunc{
    PerformerFunctor* pf;
    memFunc(PerformerFunctor* _pf) : pf(_pf) {}

    void operator()(const MemInfo &mi){
        pf->operator()(mi);
    }
};

/**
*constructor for processing speed and memory results
*/
Analyzer::Analyzer(ConfigFile *cp, const speed_map &sm, const mem_map &mm)
{
    //seperate methods handle the processing
    analyzeSpeed(cp, sm);
    analyzeMemory(cp, mm);
}

/**
*constructor for speed result analysis
*/
Analyzer::Analyzer(ConfigFile *cp, const speed_map &sm)
{
    //seperate methods handle the processing
    analyzeSpeed(cp, sm);
}

/**
*constructor for memory map result analysis
*/
Analyzer::Analyzer(ConfigFile *cp, const mem_map &mm)
{
    //seperate methods handle the processing
    analyzeMemory(cp, mm);
}

/**
*Destructor
*/
Analyzer::~Analyzer()
{
    //dtor
}

/**
*these are the method that do the actual processing and analyzing of the speed results
*/
void Analyzer::analyzeSpeed(ConfigFile *cf, const speed_map &sm)
{
        //retrieve the names of the section and add them to the section list
    for(speed_map::const_iterator it = sm.begin(); it != sm.end(); it++){
        string sect(it->first);

        //call the functors to calculate statistics for all results in that section
        for_each(it->second.begin(), it->second.end(), Paverage(&result["speed"][sect]));
        for_each(it->second.begin(), it->second.end(), Pmin(&result["speed"][sect]));
        for_each(it->second.begin(), it->second.end(), Pmax(&result["speed"][sect]));
        for_each(it->second.begin(), it->second.end(), PstdDeviation(&result["speed"][sect]));

        //this section checks if the user has requested to use customer PerformerFunctors and then retrieves and uses them
        if(cf->getUseCustomPf()){

            PerformerFunctor **pfArray = cf->getCustomPfArray();
            size_t arSize = cf->getPfArraySize();

            //loop through all the customer PerformerFunctors and use each one on the results
            for(size_t i = 0; i<arSize; i++){
                PerformerFunctor *pf = pfArray[i];

                pf->setResultArea(&result["speed"][sect]);
                for_each(it->second.begin(), it->second.end(), spdFunc(pf));
            }
        }

        sect.append(" - (speed)");
        sectionList.insert(sect);
    }
}

/**
*the method that handles the actual processing and analysis of the memory results
*/
void Analyzer::analyzeMemory(ConfigFile *cf, const mem_map &mm)
{
      //retrieve the names of the section and add them to the section list
    for(mem_map::const_iterator it = mm.begin(); it != mm.end(); it++){
        string sect(it->first);

        //call the functors to calculate statistics
        for_each(it->second.begin(), it->second.end(), Paverage(&result["memory"][sect]));
        for_each(it->second.begin(), it->second.end(), Pmin(&result["memory"][sect]));
        for_each(it->second.begin(), it->second.end(), Pmax(&result["memory"][sect]));
        for_each(it->second.begin(), it->second.end(), PstdDeviation(&result["memory"][sect]));

        //this section checks if the user has requested to use customer PerformerFunctors and then retrieves and uses them
        if(cf->getUseCustomPf()){

            PerformerFunctor **pfArray = cf->getCustomPfArray();
            size_t arSize = cf->getPfArraySize();

            //loop through all the customer PerformerFunctors and use each one on the results
            for(size_t i = 0; i<arSize; i++){
                PerformerFunctor *pf = pfArray[i];

                pf->setResultArea(&result["memory"][sect]);
                for_each(it->second.begin(), it->second.end(), memFunc(pf));
            }
        }
        sect.append(" - (memory)");
        sectionList.insert(sect);
    }
}

/**
*returns a const reference instead of a copy of the processed result as it could be a large structure
*/
const analyzed_result& Analyzer::getResult() const
{
    return result;
}

/**
*returns a copy of the processed result
*/
analyzed_result Analyzer::getResultCopy() const
{
    return result;
}

/**
*returns a const reference instead of a copy of the processed result as it could be a large structure
*/
ustring_set Analyzer::getSectionList() const
{
    return sectionList;
}
