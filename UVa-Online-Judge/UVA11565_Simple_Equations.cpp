//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 11565 - Simple Equations
//********************************************************************************

#define __cplusplus 201103L

#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <algorithm>

using namespace std;

// Helper Class: Input Stream
class InputStreamCin
{
public:
    InputStreamCin(bool sync_io=false)
    {
        std::ios::sync_with_stdio(sync_io);
    }
    virtual ~InputStreamCin() {};

    template<typename T>
    void get(T& x)
    {
        cin >> x;
    }

    template<typename T>
    void getArray(T* x, int size)
    {
        for(int i=0; i<size; ++i)
            cin >> x[i];
    }

    string getLine()
    {
        string line;
        getline(cin, line);
        return line;
    }
};

class InputStreamFile
{
public:
    InputStreamFile(string file)
    {
        fs_.open(file);
    }
    virtual ~InputStreamFile()
    {
        fs_.close();
    }

    template<typename T>
    void get(T& x)
    {
        fs_ >> x;
    }

    template<typename T>
    void getArray(T* x, int size)
    {
        for(int i=0; i<size; ++i)
            fs_ >> x[i];
    }

    string getLine()
    {
        string line;
        getline(fs_, line);
        return line;
    }

private:
    ifstream fs_;
};

// Input Stream variable
//#undef INPUT_FROM_FILE
#ifdef INPUT_FROM_FILE
InputStreamFile in("test.txt");
#else
InputStreamCin in(false);
#endif

struct solution
{
    int x, y, z;
    solution(int x, int y, int z) : x(x), y(y), z(z) {}
};

int main()
{
    int T;
    in.get(T);
    while(T--)
    {
        int A, B, C;
        in.get(A); in.get(B); in.get(C);

        vector<solution> sol;
        for(int x=-100; x<100; ++x)
        {
            int val_x = 2*x*x*x - A*x*(2*x - A) - C*x - 2*B;
            if(val_x == 0)
            {
                for(int y=x+1; y<100; ++y)
                {
                    int val_y = x*y*y + x*x*y - A*x*y + B;
                    if(val_y == 0)
                    {
                        double z = (double)B / (x*y);
                        if(z == (int)z)
                        {
                            if(z > y && y > x)
                                sol.push_back(solution(x, y, z));
                        }
                    }
                }
            }
        }

        if(!sol.empty())
        {
            for(int i=0; i<(int)sol.size(); ++i)
                printf("%d %d %d\n", sol[i].x, sol[i].y, sol[i].z);
        }
        else
            printf("No solution.\n");
    }

    return 0;
}

