/**
 * Problem: Find longest increasing run
 */

#include "../common/GenVector.hpp"
#include <iostream>
#include <algorithm>

void
findLongestRun(const IntVector& vect_int)
{
	int start = 0;
	unsigned cmax = 1, max = 1, i = 0;
	for (; i < vect_int.size()-1; ++i)
	{
		if (vect_int[i] < vect_int[i+1])
		{
			++cmax;
		}
		else
		{
			if (max < cmax)
			{
				max = cmax;
				start = i + 1 - cmax;
			}
			cmax = 1;
		}
	}
	
	if (max < cmax)
	{
		max = cmax;
		start = i + 1 - cmax;
	}

	
	std::cout<<"max seq: "<<max <<" start: "<<start<<"\n";
}

int main()
{
	IntVector vect_int = generateVector();
	printVector(vect_int);
	
	findLongestRun(vect_int);
	
	std::sort(vect_int.begin(), vect_int.end());
	findLongestRun(vect_int);
	
	std::sort(vect_int.begin(), vect_int.end(), std::greater<unsigned>());
	findLongestRun(vect_int);

	return 0;
}
