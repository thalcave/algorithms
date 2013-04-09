//fmicu: binary_search

#include <iostream>
#include <vector>
#include <algorithm>
#include "GenVector.hpp"

//! \brief A recursive binary search using STL vectors
//! \param vec The vector whose elements are to be searched
//! \param start The index of the first element in the vector
//! \param end One past the index of the last element in the vector
//! \param key The value being searched for
//! \return The index into the vector where the value is located,
//! or -1 if the value could not be found.

static int counter = 0;

template<typename T>
int binary_search(const std::vector<T>& vec, unsigned start, unsigned end, const T& key)
{


	++counter;
	// Termination condition: start index greater than end index
	if(start > end)
	{
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
		return binary_search(vec, start, middle - 1, key);
	}

	return binary_search(vec, middle + 1, end, key);
}
       
int main()
{
	unsigned searched;
	IntVector vect = generateVector(searched);

	std::sort(vect.begin(), vect.end());

	printVector(vect);
	std::cout<<"searched: "<<searched<<"\n";

	{
		clock_t ticks = clock();
		
		int res = binary_search(vect, 0, vect.size(), searched);
		std::cout<<"Res="<<res<<"\n";
		std::cout<<"counter="<<counter<<"\n";		
		std::cout << "My binary_search: "<< clock() - ticks << std::endl;
	}
		
	{
		clock_t ticks = clock();
		int res = std::binary_search(vect.begin(), vect.end(),searched);
		std::cout<<"Res="<<res<<"\n";
		std::cout << "Std::binary_search: "<< clock() - ticks << std::endl;
	}
	
	{
		clock_t ticks = clock();
		IntVector::const_iterator result = std::find(vect.begin(), vect.end(), searched);
		if( result == vect.end() ) {
			std::cout << "Did not find any element matching " << searched << std::endl;
		}              

		else {
			std::cout << "Found a matching element: " << *result << std::endl;
		}              
		std::cout << "Std::find: "<< clock() - ticks << std::endl;
	}

	
	return 0;
}
