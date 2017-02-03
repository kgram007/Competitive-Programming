//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 10382 - Watering Grass
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

int N, len, width;

struct Sprinkler
{
    int pos;
    int radius;
    double left_lim;
    double right_lim;
};

inline double getCircumSqHalfLen(int r)
{
    return sqrt(((long long)r*r - width*width/4.0));
}

inline double getLeftLim(int p, int r)
{
    return p - getCircumSqHalfLen(r);
}

inline double getRightLim(int p, int r)
{
    return p + getCircumSqHalfLen(r);
}

int findMinSprinklers(vector< Sprinkler >& sprinklers)
{
    int count = 0;
    double end_val = 0;
    int i;
    for(i=0; i<(int)sprinklers.size();)
    {
        if(sprinklers[i].left_lim <= end_val && sprinklers[i].right_lim > end_val)
        {
            int max_val = end_val;
            int max_val_index = -1;
            for(int j=i; j<(int)sprinklers.size(); ++j)
            {
                if(sprinklers[j].left_lim > end_val)
                    break;
                if(sprinklers[j].right_lim > max_val)
                {
                    max_val = sprinklers[j].right_lim;
                    max_val_index = j;
                }
            }

            if(max_val_index == -1)
                return -1;
            i = max_val_index;

            end_val = sprinklers[i].right_lim;
            count++;

            if(end_val >= len)
                break;
        }
        else
            i++;
    }

    if(end_val < len)
        return -1;
    return count;
}

int compare_sprinklers(const Sprinkler& a, const Sprinkler& b)
{
    return a.left_lim < b.left_lim;
}


// Main Function
int main()
{
    programEntry();
    //****************************************************************//
    while(1)
    {
        if( !(cin >> N >> len >> width) )
            break;

        vector< Sprinkler > sprinklers;
        for(int i=0; i<N; ++i)
        {
            int p, r; in.get(p); in.get(r);
            if(r < width/2.0)
                continue;
            sprinklers.push_back(Sprinkler{p, r, getLeftLim(p,r), getRightLim(p,r)});
        }

        // sort with position
        sort(sprinklers.begin(), sprinklers.end(), compare_sprinklers);

        cout << findMinSprinklers(sprinklers) << endl;

    }
    //****************************************************************//
    programExit();
    return 0;
}
