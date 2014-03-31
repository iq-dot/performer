#ifndef PAVERAGE_H
#define PAVERAGE_H

#include <performer/analysis/pfunctor.h>

/**
*This functor class calculates the averages for the speed and memory results.
*The values are stored in the given result_category
*/
class Paverage : public PerformerFunctor
{
    public:
        Paverage(result_category*);
        virtual ~Paverage();

        void operator()(const SpeedInfo&);
        void operator()(const MemInfo&);

    private:
        int freq;
};

#endif // PAVERAGE_H
