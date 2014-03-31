#include "performer/config/configfile.h"
#include <ctime>
#include <sstream>

using namespace std;

/**
*Constructor for loading existing result files
*/
ConfigFile::ConfigFile(const char *load):autosave(true), useTimerOffset(false), useCustomPf(false), rxml(NULL)
{
    setFileToLoad(load);
}

/**
*Constructor used for specifying new file to save results
*/
ConfigFile::ConfigFile(const char *src, const char *fname, const char *saveloc):loadfile(false), autosave(true), useTimerOffset(false), useCustomPf(false), rxml(NULL)
{
    setSourceName(src);
    setFileName(fname);
    setSaveLocation(saveloc);
}

/**
*Default constructor, does not do anything
*/
ConfigFile::ConfigFile():autosave(true), useTimerOffset(false), useCustomPf(false), rxml(NULL)
{
}

/**
*Default destructor
*/
ConfigFile::~ConfigFile()
{
}

/**
*return whether to load a file
*/
bool ConfigFile::isLoadFile()
{
    return loadfile;
}

/**
return source name as a c style string
*/
const char* ConfigFile::getSource()
{
    return source.c_str();
}

/**
*set the location and file name to be loaded
*/
void ConfigFile::setFileToLoad(const char* fileloc)
{
    file_location = fileloc;
    loadfile = true;
}

/**
*set the filename of the save file
*/
void ConfigFile::setFileName(const char* fname)
{
    filename = fname;

    //check if the user has included the .xml extension
    size_t found = filename.find(".xml");

    //if not then add the .xml extension to the filename
    if(found == string::npos){
        filename.append(".xml");
    }

    //if previously the config object was set to laod a file then overwrite the save location with the filename
    //which will make the save location the current working directory
    if(loadfile){
        file_location = filename;
    }

    loadfile = false;
}

/**
*set the save location and adjust settings to create document instead of loading a file
*/
void ConfigFile::setSaveLocation(const char* loc)
{
    file_location = loc;

    //check that the filename isn't blank, if it is then as a safety create a default filename based on a unix timestamp
    if(filename.size()==0 || filename == " "){
        stringstream ss;
        ss << time(NULL) <<".xml";
        filename = ss.str();
    }

    //check if the user has provided a slash at the end if not then add one
    if(file_location.size()>0 && file_location[file_location.size()-1] != '/'){
        file_location.append("/");
    }

    //finally set the file location to be a combination of the location + filename
    file_location.append(filename);

    loadfile = false;
}

/**
*return the file to load or where to save document including name
*/
const char* ConfigFile::getFileLocation()
{
    return file_location.c_str();
}

/**
*set the source name
*/
void ConfigFile::setSourceName(const char* src)
{
    source = src;
}

/**
*set whether to use timer offsets
*/
void ConfigFile::setUseTimerOffset(bool val)
{
    useTimerOffset = val;
}

/**
*get the value of useTimerOffset
*/
bool ConfigFile::getUseTimerOffset()
{
    return useTimerOffset;
}

/**
*Check if autosave is enabled
*/
bool ConfigFile::isAutoSave()
{
    return autosave;
}

/**
*Set an array of customer PerformerFunctors that components from the analysis module can use
*/
void ConfigFile::setCustomPf(PerformerFunctor **pfArray, size_t arrSize)
{
    customPfArray = pfArray;
    pfArraySize = arrSize;
}

/**
*Set whether to enable or disable the use of customer performer functors
*/
void ConfigFile::setUseCustomPf(bool val)
{
    useCustomPf = val;
}

/**
*Check if the use of customer PerformerFunctors is enabled or disabled
*/
bool ConfigFile::getUseCustomPf()
{
    return useCustomPf;
}

/**
*Get the array of custom PerformerFunctors if there are any
*/
PerformerFunctor** ConfigFile::getCustomPfArray()
{
    return customPfArray;
}

/**
*Get the array of custom PerformerFunctors if there are any
*/
size_t ConfigFile::getPfArraySize()
{
    return pfArraySize;
}

/**
*The the resultXML pointer
*/
void ConfigFile::setRxml(ResultXML *xml)
{
    rxml = xml;
}

/**
*Retrieve the resultXML pointer_to_binary_function
*/
ResultXML* ConfigFile::getRxml()
{
    return rxml;
}
