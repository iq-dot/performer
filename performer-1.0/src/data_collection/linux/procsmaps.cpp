#include "performer/data_collection/linux/procsmaps.h"
#include <iostream>
#include <sstream>

using namespace std;

//initialize the string variables with the regular expression that will be used
//for all instances of this class
const string ProcSmap::reStack = "\\[STack\\]";
const string ProcSmap::reHeap = "\\[heap\\]";
const string ProcSmap::reSize = "(Size:)\\s*(\\d+)\\s*(kB)\\s*";
const string ProcSmap::reRss = "(Rss:)\\s*(\\d+)\\s*(kB)\\s*";
const string ProcSmap::reShrClean = "(Shared_Clean:)\\s*(\\d+)\\s*(kB)\\s*";
const string ProcSmap::reShrDirty = "(Shared_Dirty:)\\s*(\\d+)\\s*(kB)\\s*";
const string ProcSmap::rePrivClean = "(Private_Clean:)\\s*(\\d+)\\s*(kB)\\s*";
const string ProcSmap::rePrivDirty = "(Private_Dirty:)\\s*(\\d+)\\s*(kB)\\s*";
const string ProcSmap::reRef = "(Referenced:)\\s*(\\d+)\\s*(kB)\\s*";
const string ProcSmap::reSwap = "(Swap:)\\s*(\\d+)\\s*(kB)\\s*";

//try to create and initialize the regex objects with the defined regular expressions
boost::regex ProcSmap::regStack(reStack, boost::regex_constants::icase);
boost::regex ProcSmap::regHeap(reHeap, boost::regex_constants::icase);
boost::regex ProcSmap::regSize(reSize, boost::regex_constants::icase);
boost::regex ProcSmap::regRss(reRss, boost::regex_constants::icase);
boost::regex ProcSmap::regShrClean(reShrClean, boost::regex_constants::icase);
boost::regex ProcSmap::regShrDirty(reShrDirty, boost::regex_constants::icase);
boost::regex ProcSmap::regPrivClean(rePrivClean, boost::regex_constants::icase);
boost::regex ProcSmap::regPrivDirty(rePrivDirty, boost::regex_constants::icase);
boost::regex ProcSmap::regRef(reRef, boost::regex_constants::icase);
boost::regex ProcSmap::regSwap(reRef, boost::regex_constants::icase);

//default constructor, gets and processes the smap for current process
ProcSmap::ProcSmap(MemInfo &result)
{
    procID = getpid();

	stringstream sfpath;
	sfpath << "/proc/" << procID << "/smaps";
	const char *path = sfpath.str().c_str();

	smap = fopen(path, "r");
	parse(result);
}

//gets and processes the smap for given process id
ProcSmap::ProcSmap(MemInfo &result, pid_t &proc_id):procID(proc_id)
{
	stringstream sfpath;
	sfpath << "/proc/" << procID << "/smaps";
	const char *path = sfpath.str().c_str();

	smap = fopen(path, "r");
	parse(result);
}

//default destructor
ProcSmap::~ProcSmap()
{
	fclose(smap);
}

//update the smap with the most current one at the time of calling and process the updates values
void ProcSmap::update(MemInfo &result)
{
	stringstream sfpath;
	sfpath << "/proc/" << procID << "/smaps";
	const char *path = sfpath.str().c_str();

	freopen(path, "r", smap);

	parse(result);
}

//initialize all struct values to 0
void ProcSmap::initSmapStruct(MemInfo &smapData)
{
	smapData.sharedMem=0;
	smapData.privateMem=0;
	smapData.dirtyMem=0;
	smapData.cleanMem=0;
	smapData.swapMem=0;
	smapData.refMem=0;
	smapData.sharedDirtyMem=0;
	smapData.sharedCleanMem=0;
	smapData.privateDirtyMem=0;
	smapData.privateCleanMem=0;
	smapData.rsSize=0;
	smapData.vsSize=0;

	smapData.stackSize=0;
	smapData.stackRss=0;
	smapData.stackRef=0;
	smapData.stackClean=0;
	smapData.stackDirty=0;

	smapData.heapSize=0;
	smapData.heapRss=0;
	smapData.heapRef=0;
	smapData.heapClean=0;
	smapData.heapDirty=0;
}

//parses the smap and stores the result in the smapData structure
void ProcSmap::parse(MemInfo &smapData)
{
	ProcSmap::initSmapStruct(smapData); //reset the struct that holds parsed smap data
	boost::cmatch regMatch;
	char line[255];

	while(fgets(line, sizeof line, smap)){

		//stack
		if(boost::regex_search(line, regStack)){
			ProcSmap::parseStack(smapData);
		}
		//heap
		else if(boost::regex_search(line, regHeap)){
			ProcSmap::parseHeap(smapData);
		}

		//size
		else if(boost::regex_match(line, regMatch, regSize)){
			string num = regMatch[2];
			smapData.vsSize += atoi(num.c_str());
		}
		//rss
		else if(boost::regex_match(line, regMatch, regRss)){
			string num = regMatch[2];
			smapData.rsSize += atoi(num.c_str());
		}
		//shared clean
		else if(boost::regex_match(line, regMatch, regShrClean)){
			string num = regMatch[2];
			smapData.sharedCleanMem += atoi(num.c_str());
			smapData.sharedMem += atoi(num.c_str());
			smapData.cleanMem += atoi(num.c_str());
		}
		//shared dirty
		else if(boost::regex_match(line, regMatch, regShrDirty)){
			string num = regMatch[2];
			smapData.sharedDirtyMem += atoi(num.c_str());
			smapData.sharedMem += atoi(num.c_str());
			smapData.dirtyMem += atoi(num.c_str());
		}
		//private clean
		else if(boost::regex_match(line, regMatch, regPrivClean)){
			string num = regMatch[2];
			smapData.privateCleanMem += atoi(num.c_str());
			smapData.privateMem += atoi(num.c_str());
			smapData.cleanMem += atoi(num.c_str());
		}
		//private dirty
		else if(boost::regex_match(line, regMatch, regPrivDirty)){
			string num = regMatch[2];
			smapData.privateDirtyMem += atoi(num.c_str());
			smapData.privateMem += atoi(num.c_str());
			smapData.dirtyMem += atoi(num.c_str());
		}
		//referenced
		else if(boost::regex_match(line, regMatch, regRef)){
			string num = regMatch[2];
			smapData.refMem += atoi(num.c_str());
		}
		//swap
		else if(boost::regex_match(line, regMatch, regSwap)){
			string num = regMatch[2];
			smapData.swapMem += atoi(num.c_str());
		}
	}
}

//parses the stack section of the smap
void ProcSmap::parseStack(MemInfo &smapData)
{
	boost::cmatch regMatch;
	char line[255];

	while(fgets(line, sizeof line, smap) && !boost::regex_match(line, regMatch, regSwap)){
		//size
		if(boost::regex_match(line, regMatch, regSize)){
			string num = regMatch[2];
			smapData.stackSize += atoi(num.c_str());
			smapData.vsSize += atoi(num.c_str());
		}
		//rss
		else if(boost::regex_match(line, regMatch, regRss)){
			string num = regMatch[2];
			smapData.stackRss += atoi(num.c_str());
			smapData.rsSize += atoi(num.c_str());
		}
		//shared clean
		else if(boost::regex_match(line, regMatch, regShrClean)){
			string num = regMatch[2];
			smapData.stackClean += atoi(num.c_str());
			smapData.sharedCleanMem += atoi(num.c_str());
			smapData.sharedMem += atoi(num.c_str());
			smapData.cleanMem += atoi(num.c_str());
		}
		//shared dirty
		else if(boost::regex_match(line, regMatch, regShrDirty)){
			string num = regMatch[2];
			smapData.stackDirty += atoi(num.c_str());
			smapData.sharedDirtyMem += atoi(num.c_str());
			smapData.sharedMem += atoi(num.c_str());
			smapData.dirtyMem += atoi(num.c_str());
		}
		//private clean
		else if(boost::regex_match(line, regMatch, regPrivClean)){
			string num = regMatch[2];
			smapData.stackClean += atoi(num.c_str());
			smapData.privateCleanMem += atoi(num.c_str());
			smapData.privateMem += atoi(num.c_str());
			smapData.cleanMem += atoi(num.c_str());
		}
		//private dirty
		else if(boost::regex_match(line, regMatch, regPrivDirty)){
			string num = regMatch[2];
			smapData.stackDirty += atoi(num.c_str());
			smapData.privateDirtyMem += atoi(num.c_str());
			smapData.privateMem += atoi(num.c_str());
			smapData.dirtyMem += atoi(num.c_str());
		}
		//referenced
		else if(boost::regex_match(line, regMatch, regRef)){
			string num = regMatch[2];
			smapData.stackRef += atoi(num.c_str());
			smapData.refMem += atoi(num.c_str());
		}
	}

	//swap
	if(boost::regex_match(line, regMatch, regSwap)){
		string num = regMatch[2];
		smapData.swapMem += atoi(num.c_str());
	}
}

//parses the heap section of the smap
void ProcSmap::parseHeap(MemInfo &smapData)
{
	boost::cmatch regMatch;
	char line[255];

	while(fgets(line, sizeof line, smap) && !boost::regex_match(line, regMatch, regSwap)){
		//size
		if(boost::regex_match(line, regMatch, regSize)){
			string num = regMatch[2];
			smapData.heapSize += atoi(num.c_str());
			smapData.vsSize += atoi(num.c_str());
		}
		//rss
		else if(boost::regex_match(line, regMatch, regRss)){
			string num = regMatch[2];
			smapData.heapRss += atoi(num.c_str());
			smapData.rsSize += atoi(num.c_str());
		}
		//shared clean
		else if(boost::regex_match(line, regMatch, regShrClean)){
			string num = regMatch[2];
			smapData.heapClean += atoi(num.c_str());
			smapData.sharedCleanMem += atoi(num.c_str());
			smapData.sharedMem += atoi(num.c_str());
			smapData.cleanMem += atoi(num.c_str());
		}
		//shared dirty
		else if(boost::regex_match(line, regMatch, regShrDirty)){
			string num = regMatch[2];
			smapData.heapDirty += atoi(num.c_str());
			smapData.sharedDirtyMem += atoi(num.c_str());
			smapData.sharedMem += atoi(num.c_str());
			smapData.dirtyMem += atoi(num.c_str());
		}
		//private clean
		else if(boost::regex_match(line, regMatch, regPrivClean)){
			string num = regMatch[2];
			smapData.heapClean += atoi(num.c_str());
			smapData.privateCleanMem += atoi(num.c_str());
			smapData.privateMem += atoi(num.c_str());
			smapData.cleanMem += atoi(num.c_str());
		}
		//private dirty
		else if(boost::regex_match(line, regMatch, regPrivDirty)){
			string num = regMatch[2];
			smapData.heapDirty += atoi(num.c_str());
			smapData.privateDirtyMem += atoi(num.c_str());
			smapData.privateMem += atoi(num.c_str());
			smapData.dirtyMem += atoi(num.c_str());
		}
		//referenced
		else if(boost::regex_match(line, regMatch, regRef)){
			string num = regMatch[2];
			smapData.heapRef += atoi(num.c_str());
			smapData.refMem += atoi(num.c_str());
		}
	}

	//swap
	if(boost::regex_match(line, regMatch, regSwap)){
		string num = regMatch[2];
		smapData.swapMem += atoi(num.c_str());
	}
}
