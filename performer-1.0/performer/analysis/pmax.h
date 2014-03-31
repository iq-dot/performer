#ifndef PERFORMER_FUNCT_MAX_H
#define PERFORMER_FUNCT_MAX_H

#include <performer/analysis/pfunctor.h>

/**
*This functor calculates the maximum values of the speed and memory results.
*The values are stored in the given result_category
*/
class Pmax : public PerformerFunctor
{
    public:
        Pmax(result_category *rc);
        virtual ~Pmax();

        void operator()(const SpeedInfo &si);
        void operator()(const MemInfo &si);
};

#endif // PERFORMER_FUNCT_MAX_H
