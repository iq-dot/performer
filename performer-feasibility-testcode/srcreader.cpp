#include <fstream>
#include <iostream>
#include <iomanip>
#include "srcreader.h"

using namespace std;

SrcReader::SrcReader()
{
    //ctor
}

SrcReader::~SrcReader()
{
    //dtor
}

int main()
{
    ifstream srcFile;
    srcFile.open("lintimer.h");

    if(!srcFile){
        cerr << "Error: Can't Open";
        //exit(1);
    }

    string x;
    srcFile >> x;
    cout << "File Data: " << endl << x <<endl;

    return 0;

}
