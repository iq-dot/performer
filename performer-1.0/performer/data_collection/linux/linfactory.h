#ifndef LINFACTORY_H
#define LINFACTORY_H

#include <performer/pfactory.h>

class LinFactory : public PerformerFactory
{
    public:
        LinFactory();
        ~LinFactory();

        //gives back platform specific timer and memory profilers in this case linux
        Timer* createTimer();
        MemProfiler* createMemProfiler();

    private:
        LinFactory(const LinFactory& other){};
        LinFactory& operator=(const LinFactory& other){
            return *this;
        };
};

#endif // LINFACTORY_H
