//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 272 - TEX Quotes
//********************************************************************************

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	char c;
	bool openState = false;
	while(cin.get(c))
	{
		if(c == '"')
		{
			if(openState == false)
			{
				cout << "``";
				openState = true;
			}
			else
			{
				cout << "''";
				openState = false;
			}
		}
		else
		{
			cout << c;
		}
	}

	return 0;
}

