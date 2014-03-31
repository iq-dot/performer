#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>

using namespace std;

int main()
{
	
	FILE *pf;
	stringstream scmd;
	pid_t self;
	self = getpid();
	
	/*Keep FILE open and keep polling it over time*/
	
	scmd << "/proc/" << self << "/stat";
	const char *cmd = scmd.str().c_str();
	
	pf = fopen(cmd, "r");
	
	cout << scmd.str().c_str() << endl;
	
	int n;
	char *nn;

	fscanf(pf, "%d %s", &n, nn);
	cout << "Output" << endl << n << endl << nn << endl;
	
	char buff[256];
	printf("Proc ID %d \nProc Name %s", n, nn);
	while(fgets(buff, sizeof buff, pf)){
		
		cout << buff << endl;
	}
	fclose(pf);
	
	int x;
	cin >> x;
	
	/*
	 
	char *cmd = "cat /proc/3466/smaps";
	
	FILE *pf;
   char *command="ls -l";
   char line[256];

   if ( !(pf = (FILE*)popen(command,"r")) )
   {  // If fpipe is NULL
      perror("Problems with pipe");
      exit(EXIT_FAILURE);
   }

   while ( fgets( line, sizeof line, pf))
   {
     cout << line << endl;
   }
   pclose(pf);

 */
   
	return 0;
}
