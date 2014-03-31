#include "lintimer.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

using namespace std;


int main()
{       
	
/////////////////////////////////////////////	
	
	pid_t child_pid, self;
	self = getpid();
	int pf[2];
	cout << "self: " << self << endl;

	//create pipe
	pipe(pf);
	
child_pid = fork();
if (child_pid < 0) {      /* fork() failed */
    perror("fork");
    exit(EXIT_FAILURE);
}

if (child_pid == 0) {       /* This is the child */
   cout << "Child here: " << endl;
   pid_t cp = getpid();
   
   cout << "ID: " << cp << endl;
   
   close(pf[0]);
   dup2(pf[1], 1);
   close(pf[1]);  
   
   execlp("ls", "ls", (char *) 0);
}
else{
	//parent process here
	
	close(pf[1]);
	dup2(pf[0], 0);
	//close(pf[0]);
	
	//char buf[100];
	//read(pf[0], buf, 100);
	execlp("grep", "grep", "test", (char *)0);
	
	cout << "buffer: " << endl;	
}
//////////////////////////////////////////////	

	return 0;
}
