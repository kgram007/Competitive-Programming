//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 161 - Traffic Lights
//********************************************************************************

#define __cplusplus 201103L

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <math.h>
#include <limits>
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
#include <bitset>

//***************** Debug ******************//
// - Defined with -D flag during compile time
// - undef to disable definition
//
//#undef CHECK_RUN_TIME
//#undef INPUT_FROM_FILE
#undef OUTPUT_TO_FILE
//******************************************//

using namespace std;

// Helper Class: Input Stream
class InputStream
{
public:
    template<typename T>
    void get(T& x) { cin >> x; }

    template<typename T>
    void getArray(T& x, int size) { for(int i=0; i<size; ++i) cin >> x[i]; }

    int getLine(string& line) { getline(cin, line); return line.size(); }

    void getNonEmptyLine(string& line) {  while( !getLine(line) ); }
};

// Input Stream variable
InputStream in;

// Helper: Timer
#ifdef CHECK_RUN_TIME
#include "Timer.h"
Timer _run_timer;
#endif

void programEntry()
{
#ifdef INPUT_FROM_FILE
    freopen("test.txt", "r", stdin);
#endif
#ifdef OUTPUT_TO_FILE
    freopen("out.txt", "w", stdout);
#endif
#ifdef CHECK_RUN_TIME
    _run_timer.start();
#endif
}

void programExit()
{
#ifdef CHECK_RUN_TIME
    _run_timer.printTimeMilliSec("====================\nRun Time");
#endif
}
//****************************************************************//

#define MAX_TIME_SEC    (5*3600)

enum TrafficStatus {GREEN, ORANGE, RED};
struct TrafficInfo
{
    int cycles;
    TrafficStatus status;
    TrafficInfo(int c, TrafficStatus s) : cycles(c), status(s) {};
};

int findAllGreen(vector<TrafficInfo>& traffic)
{
    int time;
    for(time=traffic[0].cycles; time<=MAX_TIME_SEC; ++time)
    {
        for(int i=0; i<(int)traffic.size(); ++i)
        {
            if((time % (2*traffic[i].cycles)) > traffic[i].cycles)
            {
                traffic[i].status = RED;
            }
            else if((time % (2*traffic[i].cycles)) >= (traffic[i].cycles-5))
            {
                traffic[i].status = ORANGE;
            }
            else
            {
                traffic[i].status = GREEN;
            }
        }

        bool found = true;
        for(int i=0; i<(int)traffic.size() && found; ++i)
        {
            if(traffic[i].status != GREEN)
                found = false;
        }
        if(found)
            return time;
    }

    return time;
}

void printTime(int time)
{
    if(time > MAX_TIME_SEC)
    {
        cout << "Signals fail to synchronise in 5 hours" << endl;
    }
    else
    {
        int hh = time/3600, mm = (time/60)%60, ss = time%60;
        cout << (hh<10 ? "0":"") << hh << ":";
        cout << (mm<10 ? "0":"") << mm << ":";
        cout << (ss<10 ? "0":"") << ss << endl;
    }
}


// Main Function
int main()
{
    programEntry();
    //******************************************//
    while(1)
    {
        vector<TrafficInfo> traffic;
        int cycles; in.get(cycles);
        if(cycles == 0) break;
        while(1)
        {
            traffic.push_back(TrafficInfo(cycles, GREEN));
            in.get(cycles);
            if(cycles == 0) break;
        }

        sort(traffic.begin(), traffic.end(), [](TrafficInfo a, TrafficInfo b) {return a.cycles < b.cycles;} );

        printTime(findAllGreen(traffic));
    }
    //******************************************//
    programExit();
    return 0;
}
