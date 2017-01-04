//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 573 The Snail
//********************************************************************************

#define __cplusplus 201103L

#include <iostream>
#include <string>

using namespace std;

#define INPUT_STREAM cin

template<typename T>
void getInput(T& x)
{
	INPUT_STREAM >> x;
}

int main()
{
	while(1)
	{
		int H, U, D, F;
		getInput(H); getInput(U); getInput(D); getInput(F);
		if(H == 0)
			break;

		int day = 0;
		bool success = false;
		double X = (U * F) / 100.0;
		double sum = 0;
		while(1)
		{
			double climb_up = U - (day*X);
			if(climb_up < 0)
				climb_up = 0;
			sum += climb_up;
			day++;
			if(sum > H)
			{
				success = true;
				break;
			}

			sum -= D;
			if(sum < 0)
			{
				success = false;
				break;
			}
		}

		if(success)
			cout << "success on day " << day << endl;
		else
			cout << "failure on day " << day << endl;
	}

	return 0;
}
