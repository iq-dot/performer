#include "performer/data_collection/linux/procstatus.h"
#include <sstream>

using namespace std;

//create regex strings
const string ProcStatus::reData = "(VmData:)\\s*(\\d+)\\s*(kB)\\s*";
const string ProcStatus::reExe = "(VmExe:)\\s*(\\d+)\\s*(kB)\\s*";
const string ProcStatus::reLib = "(VmLib:)\\s*(\\d+)\\s*(kB)\\s*";
const string ProcStatus::rePTE = "(VmPTE:)\\s*(\\d+)\\s*(kB)\\s*";

//intialize the regex objects with the regular expression strings
boost::regex ProcStatus::regData(reData, boost::regex_constants::icase);
boost::regex ProcStatus::regExe(reExe, boost::regex_constants::icase);
boost::regex ProcStatus::regLib(reLib, boost::regex_constants::icase);
boost::regex ProcStatus::regPTE(rePTE, boost::regex_constants::icase);

//default constructor, gets and processes the status file for current process
ProcStatus::ProcStatus(MemInfo &result)
{
    procID = getpid();

	stringstream sfpath;
	sfpath << "/proc/" << procID << "/status";
	const char *fpath = sfpath.str().c_str();

	pStatus = fopen(fpath, "r");
	parse(result);
}

//get and processes the status file for given process id
ProcStatus::ProcStatus(MemInfo &result, pid_t &proc_id):procID(proc_id)
{
    stringstream sfpath;
	sfpath << "/proc/" << procID << "/status";
	const char *fpath = sfpath.str().c_str();

	pStatus = fopen(fpath, "r");
	parse(result);
}

//default destructor
ProcStatus::~ProcStatus()
{
	fclose(pStatus);
}

//update the current proc status with the most recent version and process the new values
void ProcStatus::update(MemInfo &result)
{
	stringstream sfpath;
	sfpath << "/proc/" << procID << "/status";
	const char *fpath = sfpath.str().c_str();

	freopen(fpath, "r", pStatus);

	parse(result);
}

//initialize all struct values to 0
void ProcStatus::initResultStruct(MemInfo &pResult)
{
	pResult.vmData=0;
	pResult.vmExe=0;
	pResult.vmLib=0;
	pResult.vmPTE=0;
}

//parses the smap and stores the result in the smapData structure
void ProcStatus::parse(MemInfo &pResult)
{
	ProcStatus::initResultStruct(pResult); //reset the struct that holds parsed data
	boost::cmatch regMatch;
	char line[255];

	while(fgets(line, sizeof line, pStatus)){

		//vmData
		if(boost::regex_match(line, regMatch, regData)){
			string num = regMatch[2];
			pResult.vmData += atoi(num.c_str());
		}
		//vmExe
		else if(boost::regex_match(line, regMatch, regExe)){
			string num = regMatch[2];
			pResult.vmExe += atoi(num.c_str());
		}
		//vmLib
		else if(boost::regex_match(line, regMatch, regLib)){
			string num = regMatch[2];
			pResult.vmLib += atoi(num.c_str());
		}
		//vmPTE
		else if(boost::regex_match(line, regMatch, regPTE)){
			string num = regMatch[2];
			pResult.vmPTE += atoi(num.c_str());
		}
	}
}
