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
	ConfigFile *vecConf = pf->createConfigObject("vector", "vecResult", "results");
	ConfigFile *listConf = pf->createConfigObject("list", "listResult.xml", "results/");
	ConfigFile *setConf = pf->createConfigObject("set", "setResult.xml", "results/");
	
	//create data collectors
	DataCollector *vecDc = pf->createDataCollector(vecConf);
	DataCollector *listDc = pf->createDataCollector(listConf);
	DataCollector *setDc = pf->createDataCollector(setConf);
	
	//create a vector, list and set of ints
	vector<int> intVec;
	list<int> intList;
	set<int> intSet;
	
	//add operations to fill all three containers
	
	vecDc->startSection("push_back"); //measure from here
	
	for(int i=0; i<10; i++){
		intVec.push_back(i);
	}
	
	vecDc->stopSection(); //stop measuring here
	
	listDc->startSection("insert"); //measure list push_back
	
	for(int i=0; i<10; i++){
		intList.push_back(i);
	}
	listDc->stopSection();
	
	setDc->startSection("insert"); //measure set insert
	
	for(int i=0; i<10; i++){
		intSet.insert(i);
	}
	setDc->stopSection();
	
	
	//search a value in the container
	
	vecDc->startSection("find"); //measure find algorithm for vector
	find(intVec.begin(), intVec.end(), 5);
	vecDc->stopSection();
	
	listDc->startSection("find"); //measure find algorithm for list
	find(intList.begin(), intList.end(), 5);
	listDc->stopSection();
	
	setDc->startSection("find"); //measure find find algorithm for set
	find(intSet.begin(), intSet.end(), 5);	
	setDc->stopSection();
	
	//erase
	
	vecDc->startSection("erase"); //measure erase algorithm for vector
	intVec.erase(intVec.begin(), intVec.end());
	vecDc->stopSection();
	
	listDc->startSection("erase"); //measure erase algorithm for list
	intList.erase(intList.begin(), intList.end());
	listDc->stopSection();
	
	setDc->startSection("erase"); //measure erase algorithm for set
	intSet.erase(intSet.begin(), intSet.end());
	setDc->stopSection();
	
	//insert operatins to refill containers
	
	vecDc->startSection("insert");
	for(int i=0; i<=100; i++){
		intVec.push_back(i);
	}
	vecDc->stopSection();
	
	listDc->startSection("insert");
	for(int i=0; i<100; i++){
		intList.push_back(i);
	}
	listDc->stopSection();
	
	setDc->startSection("insert");
	for(int i=0; i<100; i++){
		intSet.insert(i);
	}
	setDc->stopSection();
	
	//modify values via fill algorithm in container
	int y = 1;
	
	vecDc->startSection("fill"); //measure fill algorithm with vector
	fill(intVec.begin(), intVec.end(), (++y)*2);
	vecDc->stopSection();
	
	y = 1;
	listDc->startSection("fill"); //measure fill algorithm with list
	fill(intVec.begin(), intVec.end(), (++y)*2);
	listDc->stopSection();
	
	y = 1;
	setDc->startSection("fill"); //measure fill algorithm with set
	fill(intVec.begin(), intVec.end(), (++y)*2);
	setDc->stopSection();
	
	//clear all containers
	
	vecDc->startSection("clear"); //measure clear operation with vector
	intVec.clear();
	vecDc->stopSection();
	
	listDc->startSection("clear"); //measure clear operation with list
	intList.clear();
	listDc->stopSection();
	
	setDc->startSection("clear"); //measure clear operation with set
	intSet.clear();
	setDc->stopSection();
	
	return 0;
}
