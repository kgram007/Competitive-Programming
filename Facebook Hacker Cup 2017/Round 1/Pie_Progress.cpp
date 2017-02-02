//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : Facebook Hacker Cup 2017 Round 1
// Problem ID/title : Pie Progress
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
#undef CHECK_RUN_TIME
#undef INPUT_FROM_FILE
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

    string getLine() { string s; getline(cin, s); return s; }

    string getNonEmptyLine() { string s; getline(cin >> ws, s); return s; }
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
	//****************************************************************//
    int testcase_num = 1;
    int T; in.get(T);
    while(T--)
    {
        int N, M;
        in.get(N); in.get(M);
        int arr[N][M];

        for(int i=0; i<N; ++i)
        {
            for(int j=0; j<M; ++j)
                in.get(arr[i][j]);
            sort(arr[i], arr[i]+M);
        }

        int tax = 0;
        int cost = 0;
        int day_count[N] = {0};

        for(int i=0; i<N; ++i)
        {
            int taken_day = i;
            int min_cost_i = cost + arr[i][0];
            int min_tax_i = tax + 1;
            for(int j=0; j<i; ++j)
            {
                if(day_count[j] >= M)
                    continue;

                int cost_curr = cost + arr[j][ day_count[j] ];
                int tax_curr = tax - (day_count[j]*day_count[j]) + ((day_count[j]+1)*(day_count[j]+1));
                if(cost_curr+tax_curr < min_cost_i+min_tax_i)
                {
                    min_cost_i = cost_curr;
                    min_tax_i = tax_curr;
                    taken_day = j;
                }
            }

            cost = min_cost_i;
            tax = min_tax_i;
            day_count[taken_day]++;
        }

        cout << "Case #" << testcase_num++ << ": " << (cost+tax) << endl;
    }

	//****************************************************************//
    programExit();
    return 0;
}
