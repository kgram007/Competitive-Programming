/********************************************************************************\
 * Author           : Ramsundar K G (kgram007@gmail.com)
 * Online judge     : UVa Online Judge
 * Problem ID/title : 130 - Roman Roulette
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

   int n, k;
   int people[100];
   int total;
   int cur_person;
   int dead_person;
   int alive_person_num;
   int count;

   while(1)
   {
      in.get(n);
      in.get(k);
      if(n == 0 && k == 0)
         break;

      for(int i = 0; i < n; i++)
      {
         people[i] = i+1;
      }

      total = n;
      cur_person = -1;
      while(total > 1)
      {
         total--;

         // Count k and kill the person
         count = 0;
         while(count < k)
         {
            cur_person++;
            if(cur_person >= n)
               cur_person = 0;

            if(people[cur_person] > 0)
               count++;
         }
         people[cur_person] = 0;

         dead_person = cur_person;
         cur_person--;

         // Count further k and swap
         count = 0;
         while(count < k)
         {
            cur_person++;
            if(cur_person >= n)
               cur_person = 0;

            if(people[cur_person] > 0)
               count++;
         }
         people[dead_person] = people[cur_person];
         people[cur_person] = 0;

         cur_person = dead_person;

         #if 0
         // Debug: Print array
         for(int i = 0; i < n; i++)
            cout << people[i] << " ";
         cout << endl;
         #endif
      }

      for(int i = 0; i < n; i++)
      {
         if(people[i] > 0)
         {
            alive_person_num = people[i];
            break;
         }
      }

      cout << ((n - alive_person_num + 1) % n) + 1 << endl;
}

    //******************************************//
    programExit();
    return 0;
}
