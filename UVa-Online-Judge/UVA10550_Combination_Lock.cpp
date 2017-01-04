//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 10550 - Combination Lock
//********************************************************************************

#include <iostream>
#include <string>

using namespace std;

int main()
{
	int start, first, second, third;
	while(1)
	{
		cin >> start >> first >> second >> third;
		if(start == 0 && first == 0 && second == 0 && third == 0)
			break;

		int sum = 720;

		int first_deg = (start - first) * 9;
		if(first_deg < 0)
			first_deg += 360;
		sum += first_deg;

		int second_deg = (second - first) * 9;
		if(second_deg < 0)
			second_deg += 360;
		sum += 360 + second_deg;

		int third_deg = (second - third) * 9;
		if(third_deg < 0)
			third_deg += 360;
		sum += third_deg;

		cout << sum << endl;
	}

	return 0;
}

