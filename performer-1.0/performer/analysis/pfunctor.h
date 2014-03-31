#ifndef PERFORMERFUNCTOR_H_INCLUDED
#define PERFORMERFUNCTOR_H_INCLUDED

#include "performer/data_collection/pstructs.h"

/**
*This class is the base class for creating all function objects to be used on the speed and memory results.
*All function objects in the framework will inherit from this class and any user wishing to create their own
*function objects to be used alongside the framework must also inherit from this class
*/
class PerformerFunctor
{
    public:
        PerformerFunctor(const char* categoryName, result_category*);
        PerformerFunctor(const char* categoryName);
        virtual ~PerformerFunctor();

        //function operator overloaded for both SpeedInfo and MemInfo structure
        virtual void operator()(const SpeedInfo&) = 0;
        virtual void operator()(const MemInfo&) = 0;

        virtual const char* getCategory() const;
        virtual void setResultArea(result_category*);

    protected:
        result_category *rc; //this is where the processed results will be stored

    private:
        const char* category; //this category specifies what is being processed, e.g. Average, Max value etc
};

#endif // PERFORMERFUNCTOR_H_INCLUDED
