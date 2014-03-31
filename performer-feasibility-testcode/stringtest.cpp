#include <ctime>
#include <sstream>
#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	char* s= "hello/";
	char* s2 = "add-on";
	
	cout << strlen(s) << endl;
	cout << s+5 << endl;
	
	if(strcmp(s+5, "/")==0){
		cout << "string true" << endl;
		strcat(s,s2);
		cout << s3 << endl;
	}
	
	return 0;
}
