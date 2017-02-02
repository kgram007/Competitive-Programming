//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : Facebook Hacker Cup 2017 Qualification Round
// Problem ID/title : Lazy Loading
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

#define MIN_BAG_WEIGHT  (50)

// Main Function
int main()
{
    programEntry();
	//****************************************************************//
    int testcase_num = 1;
    int T; in.get(T);
    while(T--)
    {
        int N; in.get(N);
        vector<int> items(N);
        for(int i=0; i<N; ++i)
        {
            int w; in.get(w);
            items[i] = w;
        }

        sort(items.begin(), items.end(), [](int a, int b){ return a > b; });

        int trips = 0;
        int i = 0;
        int j = N-1;
        while(i <= j)
        {
            int k = (MIN_BAG_WEIGHT + items[i] - 1) / items[i];
            if(j-(k-1) < i)
                break;

            trips++;
            j -= (k - 1);
            i++;
        }

        cout << "Case #" << testcase_num++ << ": " << trips << endl;
    }

	//****************************************************************//
    programExit();
    return 0;
}
