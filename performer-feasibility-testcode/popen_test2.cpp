#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
	
	FILE *pf;
	//char *cmd = "cat /proc/4601/stat";
	char buff[256];
	
	pf = fopen("/proc/4601/stat", "r");
	
	int n;
	char *nn;
	fscanf(pf, "%d %s", &n, nn);
	cout << "Output" << endl << n << endl << nn << endl;
	
	while(fgets(buff, sizeof buff, pf)){
		
		//printf("%s", buff);
	}
	pclose(pf);
	
	/*
	
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
