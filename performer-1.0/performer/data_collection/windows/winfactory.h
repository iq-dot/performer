#ifndef WINFACTORY_H
#define WINFACTORY_H

#include "performer/performfactory.h"

class WinFactory : public PerformerFactory
{
    public:
        WinFactory();
        ~WinFactory();

        //gives back platform specific timer and memory profilers in this case windows
        Timer* createTimer();
        MemProfiler* createMemProfiler();

    private:
        WinFactory(const WinFactory& other){};
        WinFactory& operator=(const WinFactory& other){
            return *this;
        };
};

#endif // WINFACTORY_H
