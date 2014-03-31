#include "procsmaps.h"
#include "procstatus.cpp"
#include <iostream>

using namespace std;

int main()
{
	MemInfo st;
	ProcSmap p(st);
	MemInfo pst;
	ProcStatus ps(pst);
	
	cout << st.rsSize << endl << "asdf" << endl;
	cout << st.vsSize << endl;
	cout << st.stackRss << endl;
	cout << st.heapRss << endl;
	cout << st.stackSize << endl;
	cout << st.heapSize << endl;
	
	cout << endl;
	cout << pst.vmData << endl;
	cout << pst.vmExe << endl;
	cout << pst.vmLib << endl;
	cout << pst.vmPTE << endl;
	
	int i;
	cin >> i;
	cout << st.rsSize << endl;
	p.update(st);
	cout << st.rsSize << endl;
	
	ps.update(pst);
	cout << endl;
	cout << pst.vmData << endl;
	cout << pst.vmExe << endl;
	cout << pst.vmLib << endl;
	cout << pst.vmPTE << endl;
	
	return 0;
}
