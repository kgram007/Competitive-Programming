//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 12356 - Army Buddies (Method 1)
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

list< int > soldiers_list;
list<int>::iterator* soldiers_list_map = NULL;

pair<int, int> killSoldiers(list<int>::iterator itr_L,  list<int>::iterator itr_R)
{
	int L = -1;
	int R = -1;
	int L_alive = -1;
	int R_alive = -1;

	if(itr_L != list<int>::iterator() && itr_L != soldiers_list.begin())
		L = *itr_L;
	if(itr_R != list<int>::iterator() && itr_R != soldiers_list.end())
		R = *itr_R;

	if(L > 0 && prev(itr_L) != soldiers_list.begin())
		L_alive = *prev(itr_L);
	if(R > 0 && next(itr_R) != soldiers_list.end())
		R_alive = *(next(itr_R));

	if(itr_L == soldiers_list.begin())
		itr_L++;
	soldiers_list.erase(itr_L, itr_R);
	if(itr_R != soldiers_list.end())
		soldiers_list.erase(itr_R);

	for(int i=L; i<=R; ++i)
		soldiers_list_map[i] = list<int>::iterator();

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

		soldiers_list.clear();
		if(soldiers_list_map != NULL)
			delete soldiers_list_map;
		soldiers_list_map = new list<int>::iterator[S+1];
		for(int i=0; i<=S; ++i)
		{
			soldiers_list.push_back(i);
			soldiers_list_map[i] = prev( soldiers_list.end() );
		}

		int L, R;
		pair<int, int> alive_pair;
		for(int i=0; i<B; ++i)
		{
			in.get(L); in.get(R);
			alive_pair = killSoldiers(soldiers_list_map[L], soldiers_list_map[R]);
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

