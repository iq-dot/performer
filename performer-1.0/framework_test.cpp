#include "resultxml.h"
#include <iostream>

using namespace std;

int main()
{
    ResultXML xp("test.xml", " ");
    xp.save();
    cout << "what?" << endl;
    int i;
    cin >> i;
    return 0;
}
