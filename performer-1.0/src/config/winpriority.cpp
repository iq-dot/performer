#include <windows.h>
#include "performer/data_collection/configfile.h"

bool changePriority(ConfigFile::ProcPriority priority)
{
    BOOL chk;
    if(priority == ConfigFile::NORMAL){
        chk = SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
    }
    else if(priority == ConfigFile::HIGH){
        chk = SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
    }
    else if(priority == ConfigFile::HIGHER){
        chk = SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
    }
    else if(priority == ConfigFile::HIGHEST){
        chk = SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
    }

    if(chk == 0){
        return false;
    }
    else{
        return true;
    }
}

//add factory function in perfromerfactory with extern c
//extern "c" treats functions as c functions instead of c++ functions
//it uses c linkage isntead of c++ lingage
//it prevents name mangling as done by c++ compilers, which ties it to that compiler and version
