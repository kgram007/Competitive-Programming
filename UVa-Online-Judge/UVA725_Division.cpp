//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : UVA725 - Division (Method 1)
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

int getNumber(int n[])
{
    return (n[4]*10000 + n[3]*1000 + n[2]*100 + n[1]*10 + n[0]);
}

bool checkPairUniqueDigits(int x, int y)
{
    int n_x[5], n_y[5];
    for(int i=0; i<5; ++i)
    { n_x[i] = x % 10; x /= 10; }

    for(int i=0; i<5; ++i)
    { n_y[i] = y % 10; y /= 10; }

    for(int i=0; i<5; ++i)
        for(int j=0; j<5; ++j)
            if(n_x[i] == n_y[j])
                return false;

    return true;
}

void genFiveDigitUnique_Vec(vector<int>& vec)
{
    int num[5] = {0, 1, 2, 3, 4};
    for(int d4=0; d4<=9; d4++)
    {
        num[4] = d4;
        for(int d3=0; d3<=9; d3++)
        {
            if(d3 == d4) continue;
            num[3] = d3;
            for(int d2=0; d2<=9; d2++)
            {
                if(d2 == d3 || d2 == d4) continue;
                num[2] = d2;
                for(int d1=0; d1<=9; d1++)
                {
                    if(d1 == d2 || d1 == d3 || d1 == d4) continue;
                    num[1] = d1;
                    for(int d0=0; d0<=9; d0++)
                    {
                        if(d0 == d1 || d0 == d2 || d0 == d3 || d0 == d4) continue;
                        num[0] = d0;
                        vec.push_back(getNumber(num));
                    }
                }
            }
        }
    }
}

void genFiveDigitUnique_Hash(unordered_set<int>& set)
{
    int num[5] = {0, 1, 2, 3, 4};
    for(int d4=0; d4<=9; d4++)
    {
        num[4] = d4;
        for(int d3=0; d3<=9; d3++)
        {
            if(d3 == d4) continue;
            num[3] = d3;
            for(int d2=0; d2<=9; d2++)
            {
                if(d2 == d3 || d2 == d4) continue;
                num[2] = d2;
                for(int d1=0; d1<=9; d1++)
                {
                    if(d1 == d2 || d1 == d3 || d1 == d4) continue;
                    num[1] = d1;
                    for(int d0=0; d0<=9; d0++)
                    {
                        if(d0 == d1 || d0 == d2 || d0 == d3 || d0 == d4) continue;
                        num[0] = d0;
                        set.insert(getNumber(num));
                    }
                }
            }
        }
    }
}

bool comparaeNums(pair<int,int> a, pair<int,int> b)
{
    if(a.first < b.first)
        return true;
    else if(a.first > b.first)
        return false;
    else if(a.second < b.second)
        return true;
    else
        return false;

}

int main()
{
    unordered_set<int> five_digits_set;
    genFiveDigitUnique_Hash(five_digits_set);

    cout << five_digits_set.size() << endl;

    bool first_testcase = true;
    while(1)
    {
        int N;
        in.get(N);
        if(N == 0)
            break;

        if(!first_testcase)
            cout << endl;
        else
            first_testcase = false;

        vector<pair<int, int>> valid_pairs;
        unordered_set<int>::iterator itr;
        for(itr = five_digits_set.begin(); itr != five_digits_set.end(); ++itr)
        {
            int x = *itr;
            int y = N * x;
            if(five_digits_set.find(y) != five_digits_set.end())
            {
                if(checkPairUniqueDigits(x, y))
                    valid_pairs.push_back(pair<int,int>(y, x));
            }
        }

        if(!valid_pairs.empty())
        {
            sort(valid_pairs.begin(), valid_pairs.end(), comparaeNums);
            for(int i=0; i<(int)valid_pairs.size(); ++i)
            {
                int y = valid_pairs[i].first;
                int x = valid_pairs[i].second;
                cout << (y<10000 ? "0" : "") << y << " / " << (x<10000 ? "0" : "") << x << flush;
                cout << " = " << N << endl;
            }
        }
        else
            cout << "There are no solutions for " << N << "." << endl;
    }

    return 0;
}

