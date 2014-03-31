#ifndef COMPARER_H
#define COMPARER_H

#include <performer/analysis/analyzer.h>
#include <sstream>

class Comparer
{
    public:
        Comparer(const analyzed_result &ar1, const analyzed_result &ar2);
        virtual ~Comparer();

        void printComparison();

    private:
        std::stringstream spdComps;
        std::stringstream memComps;

        void memCompare(const analyzed_result&, const analyzed_result&);
        void spdCompare(const analyzed_result&, const analyzed_result&);
};

#endif // COMPARER_H
