//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 696 - How Many Knights
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
	void getArray(T& x, int size)
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
	void getArray(T& x, int size)
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

int main()
{
    while(1)
    {
        int m_, n_;
        in.get(m_); in.get(n_);
        if(m_ == 0 && n_ == 0)
            break;

        double m = m_;
        double n = n_;
        if(m > n)
            swap(m, n);

        int count = 0;
        if(m == 1)
        {
            count = n;
        }
        else if(m == 2)
        {
            if((int)n%4 == 0)
                count = n;
            else if((int)n%4 == 1 || (int)n%4 == 3)
                count = n + 1;
            else if((int)n%4 == 2)
                count = n + 2;
        }
        else
        {
            count = (ceil(m/2) * ceil(n/2)) + (floor(m/2) * floor(n/2));
        }

        cout << count << " knights may be placed on a " << m_ << " row " << n_ << " column board." << endl;
    }

	return 0;
}

