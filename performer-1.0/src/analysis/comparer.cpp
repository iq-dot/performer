#include "performer/analysis/comparer.h"

using namespace std;

Comparer::Comparer(const analyzed_result &ar1, const analyzed_result &ar2)
{
    spdCompare(ar1, ar2);
    memCompare(ar1, ar2);

}

Comparer::~Comparer()
{
    //dtor
}

void Comparer::spdCompare(const analyzed_result &ar1, const analyzed_result &ar2)
{
    int ar1Score = 0, ar2Score = 0;

}

void Comparer::memCompare(const analyzed_result &ar1, const analyzed_result &ar2)
{
    int ar1Score = 0, ar2Score = 0;

}

void Comparer::printComparison()
{

}

