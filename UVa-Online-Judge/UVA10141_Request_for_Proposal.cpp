/********************************************************************************\
 * Author           : Ramsundar K G (kgram007@gmail.com)
 * Online judge     : UVa Online Judge
 * Problem ID/title : 10141 - Request for Proposal
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

typedef struct Proposal_Tag
{
   string name;
   double price;
   int num_req;
} Proposal;

// Main Function
int main()
{
    programEntry();
    //******************************************//

    int tc = 1;
    while(1)
    {
       int n, p;
       in.get(n); in.get(p);
       if(n == 0 && p == 0)
          break;

       for(int i=0; i<n; ++i)
       {
          string s;
          in.getNonEmptyLine(s);
       }

       Proposal prop, best_prop;
       for(int i=0; i<p; ++i)
       {
          in.getNonEmptyLine(prop.name);
          in.get(prop.price);
          in.get(prop.num_req);
          for(int j=0; j<prop.num_req; ++j)
          {
             string s;
             in.getNonEmptyLine(s);
          }

          if(i == 0)
          {
             best_prop = prop;
          }
          else if(prop.num_req > best_prop.num_req)
          {
             best_prop = prop;
          }
          else if(prop.num_req == best_prop.num_req)
          {
             if(prop.price < best_prop.price)
             {
                best_prop = prop;
             }
          }
       }

       if(tc > 1) cout << endl;
       cout << "RFP #" << tc++ << endl;
       cout << best_prop.name << endl;
    }

    //******************************************//
    programExit();
    return 0;
}
