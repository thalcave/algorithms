/*
 * Problem: find k-th element in vector
 * Solution: use partial selection sort: sort only the first kth elements using selection sort (find min in vector, move it to first position)
 * find the minimum value and move it to the beginning, repeating on the remaining list until we have accumulated k elements, and then return the kth element
 * 
 */

#include "../common/GenVector.hpp"
#include <iostream>
#include <algorithm>

void
partialSort(IntVector& vect_int, unsigned k)
{
	for (unsigned i = 0; i < k; ++i)
	{
		unsigned min_index = i;
		unsigned min_val = vect_int.at(i);
		
		for (unsigned j = i+1; j < vect_int.size(); ++j)
		{
			if (vect_int.at(j) < min_val)
			{
				min_val = vect_int.at(j);
				min_index = j;
			}
		}
		
		if (min_index != i)
		{
			std::swap(vect_int.at(i), vect_int.at(min_index));
		}
	}
}


int main()
{
	IntVector vect_int = generateVector();
	printVector(vect_int);
	
	IntVector copy(vect_int);
	std::sort(copy.begin(), copy.end());
	
	unsigned k = vect_int.size()/2;
	std::cout<<"k: "<<k<<"\n";
	
	partialSort(vect_int, k);
	
	printVector(vect_int);
	printVector(copy);
	
	std::cout<<"kth element: "<<vect_int.at(k-1)<<"\n";
	std::cout<<"copy kth element: "<<copy.at(k-1)<<"\n";
	
	return 0;
}