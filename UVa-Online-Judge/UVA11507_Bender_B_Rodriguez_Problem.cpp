/********************************************************************************\
 * Author           : Ramsundar K G (kgram007@gmail.com)
 * Online judge     : UVa Online Judge
 * Problem ID/title : 11507 - Bender B. Rodríguez Problem
\********************************************************************************/

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

/****************** Debug *******************\
 * - Defined with -D flag during compile time
 * - undef to disable definition
\********************************************/
//#undef CHECK_RUN_TIME
//#undef INPUT_FROM_FILE
#undef OUTPUT_TO_FILE
/*******************************************/

using namespace std;

// Useful Typedefs
typedef signed char        s8;
typedef signed short       s16;
typedef signed             s32;
typedef signed long long   s64;
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned           u32;
typedef unsigned long long u64;

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

int dir;

unordered_map<string, int> dir_str_2_num{
   {"+x", 1},
   {"-x", -1},
   {"+y", 2},
   {"-y", -2},
   {"+z", 3},
   {"-z", -3}
};

unordered_map<int, string> dir_num_2_str{
   {1,  "+x"},
   {-1, "-x"},
   {2,  "+y"},
   {-2, "-y"},
   {3,  "+z"},
   {-3, "-z"}
};

void updateDir(int new_dir)
{
   if(dir == 1)
      dir = new_dir;
   else if(dir == -1)
      dir = -new_dir;
   else if(dir == new_dir)
      dir = -1;
   else if(dir == -new_dir)
      dir = 1;
}

// Main Function
int main()
{
    programEntry();
    //******************************************//

    while(1)
    {
       int L;
       in.get(L);
       if(L == 0)
          break;

       dir = dir_str_2_num["+x"];
       for(int i=0; i<L-1; ++i)
       {
          string s;
          in.get(s);
          if(s == "No")
             continue;
          else
            updateDir(dir_str_2_num[s]);
       }

       cout << dir_num_2_str[dir] << endl;
    }

    //******************************************//
    programExit();
    return 0;
}
