//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 129 - Krypton Factor
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

bool checkHard(string s)
{
    int n = s.length();
    for(int i=n-1, j=1; i>=(n+1)/2; --i, ++j)
    {
        //cout << "--> " << s.substr(n-2*j,j) << " " << s.substr(i) << " = " << (s.substr(n-2*j,j) == s.substr(i)) << endl;
        if(s.substr(n-2*j,j) == s.substr(i))
            return false;
    }
    return true;
}

void printSeq(const string& s)
{
    for(int i=0; i<(int)s.length(); ++i)
    {
        if(i > 0)
        {
            if(i%64 == 0)
                cout << "\n";
            else if(i%4 == 0)
                cout << " ";
        }
        cout << s[i];
    }
    cout << "\n" << s.length() << endl;
}

bool getHardSeq(string prefix, int& count, int n, int L)
{
    if(count == n)
    {
        printSeq(prefix);
        return true;
    }

    for(int i=0; i<L; ++i)
    {
        char sufix = 'A' + i;
        if(checkHard(prefix + sufix))
        {
            count++;
            if( getHardSeq(prefix + sufix, count, n, L) )
                return true;
        }
    }

    return false;
}

void getHardSeq(int n, int L)
{
    int count = 0;
    getHardSeq("", count, n, L);
}


// Main Function
int main()
{
    programEntry();
    //****************************************************************//
    while(1)
    {
        int n, L;
        in.get(n); in.get(L);
        if(n == 0 && L == 0)
            break;

        getHardSeq(n, L);

    }
    //****************************************************************//
    programExit();
    return 0;
}
