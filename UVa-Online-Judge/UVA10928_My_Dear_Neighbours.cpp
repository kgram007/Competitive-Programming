//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 10928 - My Dear Neighbours
//********************************************************************************

#define __cplusplus 201103L

#include <iostream>
#include <string>
#include <sstream>
#include <limits>
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
	void getArray(T& x, int size)
	{
		for(int i=0; i<size; ++i)
			cin >> x[i];
	}

	void getLine(string& line)
	{
		getline(cin, line);
	}

    void ignore()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

    void getLine(string& line)
    {
        getline(fs_, line);
    }

    void ignore()
    {
        fs_.ignore(numeric_limits<streamsize>::max(), '\n');
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
    int T;
    in.get(T); in.ignore();
    while(T--)
    {
        int P;
        in.get(P); in.ignore();
        vector< int > indices;
        int min_spaces = numeric_limits<int>::max();
        for(int i=0; i<P; ++i)
        {
            string line;
            in.getLine(line);

            int spaces = std::count(line.begin(), line.end(), ' ') + 1;
            indices.push_back(spaces);
            if(spaces < min_spaces)
                min_spaces = spaces;
        }

        stringstream out_iss;
        for(int i=0; i<P; ++i)
        {
            if(indices[i] == min_spaces)
                out_iss << (i+1) << " ";
        }
        string out_str = out_iss.str();
        cout << out_str.substr(0, out_str.size()-1) << endl;
    }

	return 0;
}

