//Problem: find the closest value smaller than N
//Solution: modify the binary search

#include <iostream>
#include <vector>
#include <algorithm>
#include "GenVector.hpp"

template<typename T>
int mbinary_search(const std::vector<T>& vec, int start, int end, const T& key)
{
	// Termination condition: start index greater than end index
	if(start > end)
	{
		if (end == -1)
		{
			std::cout<<"closest value: "<<vec.at(start)<<"\n";
			return -1;
		}
		
		if (start >= vec.size())
		{
			std::cout<<"Cannot find closest value\n";
			return -1;
		}
		
		std::cout<<"closest value: "<<vec.at(end)<<"\n";
		return -1;
	}

	// Find the middle element of the vector and use that for splitting
	// the array into two pieces.
	unsigned middle = (start + ((end - start) / 2));
	std::cout<<"middle: "<<middle<<"\n";
	
	
	if(vec.at(middle) == key)
	{
		return middle;
	}
	else if(vec.at(middle) > key)
	{
		return mbinary_search(vec, start, middle - 1, key);
	}

	return mbinary_search(vec, middle + 1, end, key);
}
       
int main()
{
	{
		IntVector vect(1, 100);
		unsigned searched = 99;
		mbinary_search(vect, 0, vect.size()-1, searched);
	}
	
	{
		IntVector vect(1, 100);
		unsigned searched = 101;
		mbinary_search(vect, 0, vect.size()-1, searched);
	}
	
	{
		unsigned searched;
		IntVector vect = generateVector(searched);
		++searched;

		std::sort(vect.begin(), vect.end());

		printVector(vect);
		std::cout<<"searched: "<<searched<<"\n";

		int res = mbinary_search(vect, 0, vect.size()-1, searched);
		std::cout<<"Res="<<res<<"\n";
	}
	{
		unsigned searched;
		IntVector vect = generateVector(searched);

		std::sort(vect.begin(), vect.end());
		searched = vect.at(0)-1;

		printVector(vect);
		std::cout<<"searched: "<<searched<<"\n";

		int res = mbinary_search(vect, 0, vect.size()-1, searched);
		std::cout<<"Res="<<res<<"\n";
	}
	
	return 0;
}
