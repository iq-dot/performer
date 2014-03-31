#ifndef PROCSMAPS_H
#define PROCSMAPS_H

#include <boost/regex.hpp>
#include <stdlib.h>
#include <string>
#include "performer/data_collection/pstructs.h"

class ProcSmap
{
    public:
		//takes a MemInfo structure which it will fill in with the result
		//get the smap for the current process or for the given process id
        ProcSmap(MemInfo &result);
		ProcSmap(MemInfo &result, pid_t &procid);

        virtual ~ProcSmap();

		//updates the smap with the most current smap file available at the time of call
		void update(MemInfo &result);

		//returns the data that was parsed
	//	MemInfo& getSmapData();

    private:
		//private method that initializes the structure with all values as 0, this is due to issues with some platforms
		void initSmapStruct(MemInfo &result);

		//parses the smap and store result in the given structure
		void parse(MemInfo &result);

		//parses stack and heap section of the smap, used internally
		void parseStack(MemInfo &result);
		void parseHeap(MemInfo &result);

		//holds the smap and process id
		FILE *smap;
		pid_t procID;

		//These are the variables which will hold the regular expressions as strings
		static const std::string reStack;
		static const std::string reHeap;
		static const std::string reSize;
		static const std::string reRss;
		static const std::string reShrClean;
		static const std::string reShrDirty;
		static const std::string rePrivClean;
		static const std::string rePrivDirty;
		static const std::string reRef;
		static const std::string reSwap;

		//From the boost library, these are the objects which will utilize the above regular expressions
		//There is a single regex object for each regular expression
		static boost::regex regStack;
		static boost::regex regHeap;
		static boost::regex regSize;
		static boost::regex regRss;
		static boost::regex regShrClean;
		static boost::regex regShrDirty;
		static boost::regex regPrivClean;
		static boost::regex regPrivDirty;
		static boost::regex regRef;
		static boost::regex regSwap;
};

#endif // PROCSMAPS_H
