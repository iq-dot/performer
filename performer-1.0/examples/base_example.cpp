#include <vector>
#include <list>
#include <set>
#include <iostream>
#include <algorithm>
#include <performer/performer.h>

using namespace std;

int main()
{	
	//create factory
	PerformerFactory *pf = getPerfFactory();
	
	//config objects
	ConfigFile *vecConf = pf->createConfigObject("vector", "vecResult.xml", "result/");
	ConfigFile *listConf = pf->createConfigObject("list", "listResult.xml", "results/");
	ConfigFile *setConf = pf->createConfigObject("set", "setResult.xml", "results/");
	
	//create data collector
	DataCollector *vecDc = pf->createDataCollector(vecConf);
	DataCollector *listDc = pf->createDataCollector(listConf);
	DataCollector *setDc = pf->createDataCollector(setConf);
	
	//create a vector, list and set of ints
	vector<int> intVec;
	list<int> intList;
	set<int> intSet;
	
	//insert operatins to fill all three containers
	
	vecDc->startSection("push_back"); //measure from here
	
	for(int i=0; i<10; i++){
		intVec.push_back(i);
	}
	
	vecDc->stopSection(); //stop measuring here
	
	for(int i=0; i<10; i++){
		intList.push_back(i);
	}
	for(int i=0; i<10; i++){
		intSet.insert(i);
	}
	
	//search a value in the container
	find(intVec.begin(), intVec.end(), 5);
	find(intList.begin(), intList.end(), 5);
	find(intSet.begin(), intSet.end(), 5);	
	
	//erase
	intVec.erase(intVec.begin(), intVec.end());
	intList.erase(intList.begin(), intList.end());
	intSet.erase(intSet.begin(), intSet.end());
	
	//insert operatins to refill containers
	for(int i=0; i<=100; i++){
		intVec.push_back(i);
	}
	for(int i=0; i<100; i++){
		intList.push_back(i);
	}
	for(int i=0; i<100; i++){
		intSet.insert(i);
	}
	
	//re-fill values in container
	int y = 1;
	fill(intVec.begin(), intVec.end(), (++y)*2);
	y = 1;
	fill(intVec.begin(), intVec.end(), (++y)*2);
	y = 1;
	fill(intVec.begin(), intVec.end(), (++y)*2);
	
	//clear all containers
	intVec.clear();
	intList.clear();
	intSet.clear();
	
	return 0;
}
