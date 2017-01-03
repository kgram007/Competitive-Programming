// Author: Ramsundar K G

#define __cplusplus 201103L

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <algorithm>

//*********** Debug  ************//
//#undef CHECK_RUN_TIME
//#undef INPUT_FROM_FILE
//*******************************//

using namespace std;

// Helper Class: Input Stream
class InputStreamCin
{
public:
    InputStreamCin(bool sync_io=false)
    {
        std::ios::sync_with_stdio(sync_io);
    }
    virtual ~InputStreamCin() {};

    template<typename T>
    void get(T& x)
    {
        cin >> x;
    }

    template<typename T>
    void getArray(T& x, int size)
    {
        for(int i=0; i<size; ++i)
            cin >> x[i];
    }

    int getLine(string& line)
    {
        getline(cin, line);
        return line.size();
    }

    void getNonEmptyLine(string& line)
    {
        while( !getLine(line) );
    }

    void ignore()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
};

class InputStreamFile
{
public:
    InputStreamFile(string file)
    {
        fs_.open(file);
    }
    virtual ~InputStreamFile()
    {
        fs_.close();
    }

    template<typename T>
    void get(T& x)
    {
        fs_ >> x;
    }

    template<typename T>
    void getArray(T& x, int size)
    {
        for(int i=0; i<size; ++i)
            fs_ >> x[i];
    }

    int getLine(string& line)
    {
        getline(fs_, line);
        return line.size();
    }

    void getNonEmptyLine(string& line)
    {
        while( !getLine(line) );
    }

    void ignore()
    {
        fs_.ignore(numeric_limits<streamsize>::max(), '\n');
    }

private:
    ifstream fs_;
};


// Input Stream variable
#ifdef INPUT_FROM_FILE
InputStreamFile in("test.txt");
#else
InputStreamCin in(false);
#endif

// Helper: Timer
#ifdef CHECK_RUN_TIME
#include "Timer.h"
Timer _run_timer;
#endif

void runTimerEntry()
{
#ifdef CHECK_RUN_TIME
    _run_timer.start();
#endif
}
void runTimerExit()
{
#ifdef CHECK_RUN_TIME
    _run_timer.printTimeMilliSec("====================\nRun Time");
#endif
}
//****************************************************************//

// Main Function
int main()
{
    runTimerEntry();
    //******************************************//

    // Code

    //******************************************//
    runTimerExit();
    return 0;
}
