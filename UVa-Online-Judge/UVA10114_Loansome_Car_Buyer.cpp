/********************************************************************************\
 * Author           : Ramsundar K G (kgram007@gmail.com)
 * Online judge     : UVa Online Judge
 * Problem ID/title : 10114 - Loansome Car Buyer
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


// Main Function
int main()
{
    programEntry();
    //******************************************//

    while(1)
    {
       int loan_period, n;
       double down_pay, loan;

       in.get(loan_period);
       if(loan_period < 0)
          break;
       in.get(down_pay); in.get(loan); in.get(n);

       int m;
       double dep[100];
       fill_n(dep, 100, -1);
       for(int i=0; i<n; ++i)
       {
          in.get(m);
          in.get(dep[m]);
       }

       int months = 0;
       double curr_dep = dep[0];
       double monthly_pay = loan / loan_period;
       double car_value = (down_pay + loan) * (1 - curr_dep);
       while(1)
       {
          if(loan < car_value)
             break;

          months++;
          if(dep[months] > -0.5)
             curr_dep = dep[months];

          car_value *= (1 - curr_dep);
          loan -= monthly_pay;
       }

       cout << months << string((months == 1) ? " month" : " months") << endl;
    }

    //******************************************//
    programExit();
    return 0;
}
