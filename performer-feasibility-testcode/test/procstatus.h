#ifndef PROCSTATUS_H
#define PROCSTATUS_H

#include <boost/regex.hpp>
#include <stdlib.h>
#include <string>
#include "memprof.h"

class ProcStatus
{
    public:
		//takes a MemInfo structure which it will fill in with the result
		//get the proc status file for the current process or for the given process id
		ProcStatus(MemInfo &result);
		ProcStatus(MemInfo &result, pid_t &procid);
		
        virtual ~ProcStatus(); 
		
		//update the proc status file with the most current one and process new values
		void update(MemInfo &result);
		
    private:
		//private method that initializes the structure with all values as 0, this is due to issues with some platforms
		void initResultStruct(MemInfo &result);
		
		//processes the status file and stores the parsed data
		void parse(MemInfo &result);
		
		//hold the proc status file and the process id
		FILE *pStatus;
		pid_t procID;
		
		//These are the variables which will hold the regular expressions as strings
		static const std::string reData;
		static const std::string reExe;
		static const std::string reLib;
		static const std::string rePTE;

		//From the boost library, these are the objects which will utilize the above regular expressions
		//There is a single regex object for each regular expression
		static boost::regex regData;
		static boost::regex regExe;
		static boost::regex regLib;
		static boost::regex regPTE;
};

#endif // PROCSTATUS_H
