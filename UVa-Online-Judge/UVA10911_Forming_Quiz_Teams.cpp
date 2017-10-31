//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 10911 - Forming Quiz Teams
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


#define SET_BIT(x, i)      (x = 0x01 << (i))
#define CLEAR_BIT(x, i)    (x = ~(0x01 << (i)))
#define GET_BIT(x, i)      (((x) >> (i)) & 0x01)

typedef struct House_Tag
{
   int x, y;
} House;

// Global variables
int N;
vector<House> House_List;
double* memoi_ptr;

// Functions
double findDist(House a, House b)
{
   return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}

int getFirstUnsetBit(u32 bit_mask, int start, int end)
{
   for(int i=start; i<end; ++i)
   {
      if(!GET_BIT(bit_mask, i))
         return i;
   }

   return -1;
}

double findMinDistSum(u32 bit_mask)
{
   if(memoi_ptr[bit_mask] > -0.5)
      return memoi_ptr[bit_mask];

   if(bit_mask == (u32)((1 << 2*N) - 1))
      return memoi_ptr[bit_mask] = 0;

   // Get first available house from bit mask
   int h1 = getFirstUnsetBit(bit_mask, 0, 2*N);

   double dist_min = numeric_limits<double>::max();
   for(int i=h1+1; i<2*N; ++i)
   {
      // Get second available house from bit mask
      int h2 = getFirstUnsetBit(bit_mask, i, 2*N);
      if(h2 == -1)
         break;

      double dist = findDist(House_List[h1], House_List[h2]);
      dist_min = min(dist_min, dist + findMinDistSum(bit_mask | 1 << h1 | 1 << h2));
   }

   memoi_ptr[bit_mask] = dist_min;
   return memoi_ptr[bit_mask];
}

double findMinDistSum_BF(vector<House> house_list, double dist_pair)
{
   if(house_list.size() == 0)
      return dist_pair;

   House a = house_list[0];
   house_list.erase(house_list.begin());

   double dist_sub = numeric_limits<double>::max();
   for(int i=0; i<(int)house_list.size(); ++i)
   {
      vector<House> house_list_sub = house_list;
      house_list_sub.erase(house_list_sub.begin()+i);

      double dist_ab_new = findDist(a, house_list[i]);
      dist_sub = min(dist_sub, findMinDistSum_BF(house_list_sub, dist_ab_new));
   }

   return dist_pair + dist_sub;
}

// Main Function
int main()
{
    programEntry();
    //******************************************//

    int tc = 1;
    while(1)
    {
       in.get(N);
       if(N == 0)
          break;

       House_List.clear();
       for(int i=0; i<2*N; ++i)
       {
          string name;
          int x, y;
          in.get(name); in.get(x); in.get(y);

          House_List.push_back(House{x, y});
       }

       // init memoi ptr
       memoi_ptr = new double[1 << 2*N];
       fill_n(memoi_ptr, 1 << 2*N, -1);

       //double dist = findMinDistSum_BF(House_List, 0); // Brute force
       double dist = findMinDistSum(0); // DP
       printf("Case %d: %.2f\n", tc++, dist);

       delete [] memoi_ptr;
    }

    //******************************************//
    programExit();
    return 0;
}
