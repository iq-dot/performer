#include <boost/regex.hpp>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>

using namespace std;

int main()
{
	FILE *smap;
	pid_t self;
	self = getpid();
	
	stringstream sfpath;
	sfpath << "/proc/" << self << "/smaps";
	const char *fpath = sfpath.str().c_str();
	
	smap = fopen(fpath, "r");
	
	//create storage variables;
	int stackMem=0, heapMem=0, sharedMem=0, privateMem=0, dirtyMem=0, cleanMem=0, swapMem=0, refMem=0;
	int sharedDirtyMem=0, sharedCleanMem=0, privateDirtyMem=0, privateCleanMem=0, rsSize=0, vsSize=0;
	
	//match object
	boost::cmatch regMatch;
	
	//create regex strings;
	string reStack = "\\[STack\\]";
	string reHeap = "\\[heap\\]";
	string reSize = "(Size:)\\s*(\\d+)\\s*(kB)\\s*";
	string reRss = "(Rss:)\\s*(\\d+)\\s*(kB)\\s*";
	string reShrClean = "(Shared_Clean:)\\s*(\\d+)\\s*(kB)\\s*";
	string reShrDirty = "(Shared_Dirty:)\\s*(\\d+)\\s*(kB)\\s*";
	string rePrivClean = "(Private_Clean:)\\s*(\\d+)\\s*(kB)\\s*";
	string rePrivDirty = "(Private_Dirty:)\\s*(\\d+)\\s*(kB)\\s*";
	string reRef = "(Referenced:)\\s*(\\d+)\\s*(kB)\\s*";
	string reSwap = "(Swap:)\\s*(\\d+)\\s*(kB)\\s*";
	
	boost::regex regHeap, regSize, regRss, regShrClean, regShrDirty, regPrivClean, regPrivDirty, regRef, regSwap;
	boost::regex regStack(reStack, boost::regex_constants::icase);
	
	try{
		regHeap.assign(reHeap, boost::regex_constants::icase);
		regSize.assign(reSize, boost::regex_constants::icase);
		regRss.assign(reRss, boost::regex_constants::icase);
		regShrClean.assign(reShrClean, boost::regex_constants::icase);
		regShrDirty.assign(reShrDirty, boost::regex_constants::icase);
		regPrivClean.assign(rePrivClean, boost::regex_constants::icase);
		regPrivDirty.assign(rePrivDirty, boost::regex_constants::icase);
		regRef.assign(reRef, boost::regex_constants::icase);
		regSwap.assign(reRef, boost::regex_constants::icase);
	}
	catch(boost::regex_error &e){
		cout << "Error setting up RegEx:" << e.what() << endl;
	}
	
	char line[255];
	while(fgets(line, sizeof line, smap)){
		if(boost::regex_search(line, regStack)){
			cout << "success match" << endl << line << endl;
		}
		/*
		cout << "line: " << line << endl;
		
		//size
		if(boost::regex_match(line, regMatch, regSize)){
			string num = regMatch[2];
			vsSize += atoi(num.c_str());
			cout << "Vss: " << vsSize << endl;
		}
		
		//rss
		if(boost::regex_match(line, regMatch, regRss)){
			string num = regMatch[2];
			rsSize += atoi(num.c_str());
			cout << "Rss: " << rsSize << endl;
		}
		
		//shared clean
		if(boost::regex_match(line, regMatch, regShrClean)){
			string num = regMatch[2];
			sharedCleanMem += atoi(num.c_str());
			cout << "total shr clean: " << sharedCleanMem << endl;
		}
		
		//shared dirty
		if(boost::regex_match(line, regMatch, regShrDirty)){
			string num = regMatch[2];
			sharedDirtyMem += atoi(num.c_str());
			cout << "total shr dirty: " << sharedDirtyMem << endl;
		}
		
		//private clean
		if(boost::regex_match(line, regMatch, regPrivClean)){
			string num = regMatch[2];
			privateCleanMem += atoi(num.c_str());
			cout << "total priv clean: " << privateCleanMem << endl;
		}
		
		//private dirty
		if(boost::regex_match(line, regMatch, regPrivDirty)){
			string num = regMatch[2];
			privateDirtyMem += atoi(num.c_str());
			cout << "total priv dirty: " << privateDirtyMem << endl;
		}
		
		//referenced
		if(boost::regex_match(line, regMatch, regRef)){
			string num = regMatch[2];
			refMem += atoi(num.c_str());
			cout << "total ref: " << refMem << endl;
		}
		
		//swap
		if(boost::regex_match(line, regMatch, regSwap)){
			string num = regMatch[2];
			swapMem += atoi(num.c_str());
			cout << "total swap: " << swapMem << endl;
		}
		*/
	}
	
	fclose(smap);
	int i;
	cin>>i;
	
	return 0;
}
