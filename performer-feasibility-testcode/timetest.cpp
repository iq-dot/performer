#include <ctime>
#include <sstream>
#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	const char* s= "hello";
	const char* s2 = "add-on";
	string s1(s);
	
	
	if(s1.at(s1.size()-1) == '/'){
		cout << "string true" << endl;
		s1.append(s2);
	}
	s1+=s += "/" += s2;
	cout << s1 << endl;
	
	return 0;
}
