//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : Facebook Hacker Cup 2017 Round 1
// Problem ID/title : Manic Moving
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

struct Family
{
    int pickup;
    int drop;
    int index;
    Family() : Family(0,0,0) {}
    Family(int p, int d, int i) : pickup(p), drop(d), index(i) {}
};

struct Memoi
{
    int pickup;
    int drop;
    Memoi() : Memoi(0,0) {}
    Memoi(int p, int d) : pickup(p), drop(d) {}
};

// Constants
enum eType {PICKUP, DROP};

// Global variables
int N, M, K;
int** adj_mat;
deque< Family > truck;
vector< Family > families;
vector< Memoi > memoi;


int getMemoiVal(int level, eType type)
{
    if(type == PICKUP)
        return memoi[level].pickup;
    else
        return memoi[level].drop;
}

void setMemoiVal(int level, eType type, int val)
{
    if(type == PICKUP)
        memoi[level].pickup = val;
    else
        memoi[level].drop = val;
}

void floydWarshall()
{
    for (int k = 0; k < N; ++k)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                int d1 = adj_mat[i][j], d21 = adj_mat[i][k], d22 = adj_mat[k][j];
                if (d21 == numeric_limits<int>::max() || d22 == numeric_limits<int>::max())
                    continue;

                int d2 = d21 + d22;
                if (d1 > d2)
                    adj_mat[i][j] = d2;
            }
        }
    }
}

int getOptimalGas1(int family_count, int loc, eType type, int level);

int getOptimalGas(int family_count, int loc, eType type, int level)
{
    //cout << family_count << " " << type << " " << level << endl;
    int val = getOptimalGas1(family_count, loc, type, level);
    //cout << family_count << " " << type << " " << level <<  " " << val << endl;
    return val;
}

int getOptimalGas1(int family_count, int loc, eType type, int level)
{
//    if(family_count == 2 && type == 1 && level == 5)
//        cout << "here";

    int truck_size = truck.size();
    if (family_count == K && truck_size == 0)
        return 0;

    if (getMemoiVal(level, type) == -1)
    {
        if (truck_size == 0)
        {
            int next_loc = families[family_count].pickup;
            int d = adj_mat[loc][next_loc];
            if (d == numeric_limits<int>::max())
            {
                setMemoiVal(level, type, numeric_limits<int>::max());
                return getMemoiVal(level, type);
            }

            truck.push_back(families[family_count]);
            int c = getOptimalGas(family_count, next_loc, PICKUP, level + 1);
            truck.pop_front();
            if (c == numeric_limits<int>::max())
            {
                setMemoiVal(level, type, numeric_limits<int>::max());
                return getMemoiVal(level, type);
            }

            setMemoiVal(level, type, d + c);
            return getMemoiVal(level, type);
        }
        else if (truck_size == 1)
        {
            // either add new family or remove existing family
            int new_family_to_add = truck.front().index + 1;
            int c1 = numeric_limits<int>::max();
            int c2 = numeric_limits<int>::max();

//            for(auto& a : truck)
//                cout << a.pickup << "-" << a.drop << "-" << a.index << endl;

            // possible to add new family
            if (new_family_to_add < K)
            {
                int next_loc = families[new_family_to_add].pickup;
                int d = adj_mat[loc][next_loc];
                if (d == numeric_limits<int>::max())
                {
                    c1 = numeric_limits<int>::max();
                }
                else
                {
                    truck.push_back(families[new_family_to_add]);
                    int c = getOptimalGas(family_count, next_loc, PICKUP, level + 1);
                    truck.pop_back();
                    if (c == numeric_limits<int>::max())
                    {
                        c1 = numeric_limits<int>::max();
                    }
                    else
                    {
                        c1 = c + d;
                    }
                }
            }

            // remove family in truck
            Family family_to_remove = truck.front();
            //truck.pop_back();
            int nextLoc = family_to_remove.drop;
            int d = adj_mat[loc][nextLoc];
            if (d == numeric_limits<int>::max())
            {
                c2 = numeric_limits<int>::max();
            }
            else
            {
                truck.pop_front();
                int c = getOptimalGas(family_count + 1, nextLoc, DROP, level + 1);

                truck.push_back(family_to_remove);
                if (c == numeric_limits<int>::max())
                {
                    c2 = numeric_limits<int>::max();
                }
                else
                {
                    c2 = d + c;
                }
            }

            setMemoiVal(level, type, min(c1, c2));
            return getMemoiVal(level, type);
        }
        else
        {
            Family family_to_remove = truck.front();
            //truck.pop_back();
            int nextLoc = family_to_remove.drop;
            int d = adj_mat[loc][nextLoc];
            if (d == numeric_limits<int>::max())
            {
                setMemoiVal(level, type, numeric_limits<int>::max());
                return getMemoiVal(level, type);
            }

            truck.pop_front();
            int c = getOptimalGas(family_count + 1, nextLoc, DROP, level + 1);
            truck.push_front(family_to_remove);
            if (c == numeric_limits<int>::max())
            {
                setMemoiVal(level, type, numeric_limits<int>::max());
                return getMemoiVal(level, type);
            }

            setMemoiVal(level, type, d + c);
            return getMemoiVal(level, type);
        }
    }
    else
    {
        return getMemoiVal(level, type);
    }
}

// Main Function
int main()
{
    programEntry();
	//****************************************************************//
    int testcase_num = 1;
    int T; in.get(T);
    while (T--)
    {
        truck.clear();
        families.clear();
        memoi.clear();

        in.get(N); in.get(M); in.get(K);

        // init matrix
        adj_mat = new int*[N];
        for (int i = 0; i < N; ++i)
        {
            adj_mat[i] = new int[N];
            for (int j = 0; j < N; ++j)
                if (i != j)
                    adj_mat[i][j] = numeric_limits<int>::max();
                else
                    adj_mat[i][j] = 0;
        }

        for (int i = 0; i < M; ++i)
        {
            int A, B, G;
            in.get(A); in.get(B); in.get(G);

            adj_mat[A-1][B-1] = min(adj_mat[A-1][B-1], G);
            adj_mat[B-1][A-1] = min(adj_mat[B-1][A-1], G);
        }

        for (int i = 0; i < K; ++i)
        {
            int S, D;
            in.get(S); in.get(D);
            families.push_back(Family(S-1, D-1, i));
        }

        floydWarshall();

        for (int i = 0; i < (K*2)+1; ++i)
        {
            memoi.push_back(Memoi(-1,-1));
        }

        int opt_gas = getOptimalGas(0, 0, DROP, 0);

        if (opt_gas == numeric_limits<int>::max())
            cout << "Case #" << testcase_num++ << ": " << (-1) << endl;
        else
            cout << "Case #" << testcase_num++ << ": " << opt_gas << endl;

        delete adj_mat;
    }
	//****************************************************************//
    programExit();
    return 0;
}
