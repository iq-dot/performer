#ifndef PERFORMER_FUNCMIN_H
#define PERFORMER_FUNCMIN_H

#include <performer/analysis/pfunctor.h>s

/**
*This functor calculates the minimum values of the speed and memory results.
*The values are stored in the given result_category
*/
class Pmin : public PerformerFunctor
{
    public:
        Pmin(result_category *rc);
        virtual ~Pmin();

        void operator()(const SpeedInfo &si);
        void operator()(const MemInfo &si);

    private:
        bool spdFirstCall; //defines whether this functor is being called first time for processing speed results
        bool memFirstCall; //defines whether this functor has been called first time for processing memory results
};

#endif //included
