#include <map>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	map<string, map<string, double> > stmap;
	double freq = 0;
	stmap["hello"]["value"] = ((freq* stmap["hello"]["value"]) + 9.0) / ++freq;
	
	stmap["hello"]["value"] = ((freq* stmap["hello"]["value"]) + 9.0) / ++freq;
	
	stmap["hello"]["value"] = ((freq* stmap["hello"]["value"]) + 9.0) / ++freq;
	
	cout << stmap["hello"]["value"] << endl;
	cout << (9+9+9) / 3.0 << endl;
	
	return 0;
}
