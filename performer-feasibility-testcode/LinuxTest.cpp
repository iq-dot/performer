d#include <iostream>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>

using namespace std;

int main()
{
	clock_t start = clock();
	int i = 10000000;
	while(i!=0){i--;}
	clock_t end = clock();

	timespec tspec;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tspec);

	timeval tv;
	gettimeofday(&tv, NULL);

	cout << "clock() function" <<endl;
	cout << start << endl << end << endl;
	
	cout << "timespec gettime function" << endl;
	cout <<tspec.tv_nsec<<endl << tspec.tv_sec<<endl;

	cout << "timeval gettimeofday function" << endl;
	cout << tv.tv_sec << endl << tv.tv_usec << endl;

	rusage usage;
	int chk = getrusage(RUSAGE_SELF, &usage);

	cout << "rusage getrusage function" << endl;
	cout << usage.ru_utime.tv_usec << endl << usage.ru_stime.tv_usec << endl << "Check: " << chk << endl; 

	timespec res1,res2,res3,res4;

	clock_getres(CLOCK_REALTIME, &res1);
	clock_getres(CLOCK_MONOTONIC, &res2);
	clock_getres(CLOCK_PROCESS_CPUTIME_ID, &res3);
	clock_getres(CLOCK_THREAD_CPUTIME_ID, &res4);

	cout << "resolution of CLOCK_REALTIME" << endl;
	cout << res1.tv_nsec << endl << res1.tv_sec << endl;

	cout << "resolution of CLOCK_MONOTONIC" << endl;
	cout << res2.tv_nsec << endl << res2.tv_sec << endl;

	cout << "resolution of CLOCK_PROCESS_CPUTIME_ID" << endl;
	cout << res3.tv_nsec << endl << res3.tv_sec << endl;
	
	cout << "resolution of CLOCK_THREAD_CPUTIME_ID" << endl;
	cout << res4.tv_nsec << endl << res4.tv_sec << endl;


	return 0;
} 
