//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 12356 - Army Buddies (Method 2)
//********************************************************************************

#define __cplusplus 201103L

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <list>
#include <unordered_map>
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
InputStreamCin in(false);
//InputStreamFile in("test.txt");

int* soldiers_list_next = NULL;
int* soldiers_list_prev = NULL;

pair<int, int> killSoldiers(int L, int R, int S)
{
	int L_alive = -1;
	int R_alive = -1;

	if(L > 0 && L <= S)
		L_alive = soldiers_list_prev[L];
	if(R > 0 && R <= S)
		R_alive = soldiers_list_next[R];

	soldiers_list_prev[soldiers_list_next[R]] = soldiers_list_prev[L];
	soldiers_list_next[soldiers_list_prev[L]] = soldiers_list_next[R];

	return pair<int, int>(L_alive, R_alive);
}


int main()
{
	while(1)
	{
		int S, B;
		in.get(S); in.get(B);
		if(S == 0 && B == 0)
			break;

		if(soldiers_list_next != NULL) delete soldiers_list_next;
		soldiers_list_next = new int[S+1];

		if(soldiers_list_prev != NULL) delete soldiers_list_prev;
		soldiers_list_prev = new int[S+1];

		int prev_i = 0;
		int next_i = 2;
		for(int i=1; i<=S; ++i)
		{
			soldiers_list_prev[i] = prev_i++;
			soldiers_list_next[i] = next_i++;
		}
		soldiers_list_prev[0] = 0;
		soldiers_list_next[0] = 0;
		soldiers_list_next[S] = 0;

		int L, R;
		pair<int, int> alive_pair;
		for(int i=0; i<B; ++i)
		{
			in.get(L); in.get(R);
			alive_pair = killSoldiers(L, R, S);
			if(alive_pair.first > 0)
				cout << alive_pair.first;
			else
				cout << "*";
			cout << " ";
			if(alive_pair.second > 0)
				cout << alive_pair.second;
			else
				cout << "*";
			cout << endl;
		}

		cout << "-" << endl;
	}

	return 0;
}

