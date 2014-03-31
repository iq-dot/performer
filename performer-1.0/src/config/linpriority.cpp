#include <sys/resource.h>
#include "performer/config/configfile.h"

bool changePriority(ConfigFile::ProcPriority priority)
{
    int success;
    if(priority == ConfigFile::NORMAL){
        success = setpriority(PRIO_PROCESS, 0, 0);
    }
    else if(priority == ConfigFile::HIGH){
        success = setpriority(PRIO_PROCESS, 0, 10);
    }
    else if(priority == ConfigFile::HIGHER){
        success = setpriority(PRIO_PROCESS, 0, 15);
    }
    else if(priority == ConfigFile::HIGHEST){
        success = setpriority(PRIO_PROCESS, 0, 20);
    }

    if(success == 0){
        return true;
    }
    else{
        return false;
    }
}
