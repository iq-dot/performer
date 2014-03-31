#include "performer/analysis/pfunctor.h"

PerformerFunctor::PerformerFunctor(const char* cat, result_category *rcat):rc(rcat), category(cat)
{
}

PerformerFunctor::PerformerFunctor(const char* cat):rc(NULL), category(cat)
{
}

PerformerFunctor::~PerformerFunctor()
{
}

const char* PerformerFunctor::getCategory() const
{
    return category;
}

void PerformerFunctor::setResultArea(result_category *rcat)
{
    rc = rcat;
}
