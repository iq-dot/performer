#ifndef PERF_CONFIGFILE_H
#define PERF_CONFIGFILE_H

#include "performer/analysis/pfunctor.h"
#include "performer/data_collection/resultxml.h"
#include <string>

class ConfigFile
{
    public:
        //will be used to determine whether to measure externally or measure it self (current process)
        static const int SELF = 0;
        static const int EXTERNAL_POLL = 1;

        //process priority values, they are platform independant
        enum ProcPriority{
            NORMAL = 0,
            HIGH,
            HIGHER,
            HIGHEST
        };

        //first constructor specifies a file to load, second constructor specifies a save location and name of the save file
        ConfigFile(const char *fload);
        ConfigFile(const char *src, const char *_fname, const char *saveloc = "");
        ConfigFile();

        ~ConfigFile();

        const char* getFileLocation();
        const char* getSource();

        //this takes a directory path to a file that should be loaded, it will automatically set loadfile to true
        void setFileToLoad(const char*);
        void setSaveLocation(const char*);
        void setSourceName(const char*);
        void setAutoSave(bool);

        //this will set the filename and change loadfile to false, if it was true then file_location will change to current working directory
        void setFileName(const char*);

        //check whether to load a file
        bool isLoadFile();

        //check if autosave is on
        bool isAutoSave();

        //set or disable the use of timer offsets
        void setUseTimerOffset(bool);
        bool getUseTimerOffset();

        //these are settings for using customer PerformerFunctors
        void setCustomPf(PerformerFunctor **array, size_t arraySize);
        void setUseCustomPf(bool);
        bool getUseCustomPf();
        PerformerFunctor** getCustomPfArray();
        size_t getPfArraySize();

        //sets and retrieves a pointer to the xml object in memory for the source this config object is responsible for
        void setRxml(ResultXML*);
        ResultXML* getRxml();


    private:
        std::string source; //name of the subject being measured e.g vector
        std::string file_location; //location of the file to load or directory to save results
        std::string filename; //name of the result file

        bool loadfile; //defines whether a file is being loaded or created
        bool autosave; //defines whether the framework should autosave after certain actions
        bool useTimerOffset; //sets whether to use timer offsets for speed measurements

        //contains an array of PerformerFunctor objects that the user can specify
        PerformerFunctor **customPfArray;
        size_t pfArraySize;
        bool useCustomPf;

        ResultXML *rxml;
};

#endif // CONFIGFILE_H
