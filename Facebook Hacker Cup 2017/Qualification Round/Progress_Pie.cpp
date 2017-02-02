//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : Facebook Hacker Cup 2017 Qualification Round
// Problem ID/title : Progress Pie
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

#define PI  (3.14159265358979323846)
#define RAD_TO_DEG(x)   (x * (180.0/PI))

// Main Function
int main()
{
    programEntry();
	//****************************************************************//

    const double radius_progress = 50;

    int testcase_num = 1;
    int T; in.get(T);
    while(T--)
    {
        int P, X, Y;
        in.get(P); in.get(X); in.get(Y);

        string color = "white";
        if(P > 0)
        {
            double angle_progress = ((double)P/100) * 360;

            int a = X-50;
            int b = Y-50;
            double dist_point = sqrt( a*a + b*b );
            double angle_point = RAD_TO_DEG( atan2(a, b) );
            if(angle_point < 0)
                angle_point += 360;

            if(dist_point <= radius_progress && angle_point >= 0 && angle_point <= angle_progress)
                color = "black";
        }

        cout << "Case #" << testcase_num++ << ": " << color << endl;
    }

	//****************************************************************//
    programExit();
    return 0;
}
