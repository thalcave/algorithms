#include "../common/GenVector.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

/*
 * Problem: return kth smallest element of a vector
 * Solution: uses the same overall approach as quicksort, choosing one element as a pivot and partitioning the data in two based on the pivot, accordingly as less than or greater than the pivot. 
 * However, instead of recursing into both sides, as in quicksort, quickselect only recurses into one side – the side with the element it is searching for. 
 * This reduces the average complexity from O(n log n) (in quicksort) to O(n) (in quickselect).
 */

/*
 * partition an array in 2: left is smaller than pivot, right is greater
 * 
 */
unsigned
partition(IntVector& vect_int, unsigned left, unsigned right, unsigned k)
{
	if (vect_int.empty())
	{
		throw std::runtime_error("empty vector");
	}
	/*if (vect_int.size() == 1)
	{
		return vect_int.at(0);
	}*/
	
	unsigned pivot = vect_int.at(k);
	unsigned store_index = left;
	
	//swap pivot with last element
	std::swap(vect_int.at(k), vect_int.at(right));
	
	for (unsigned i = left; i < right; ++i)
	{
		if (vect_int.at(i) < pivot)
		{
			std::swap(vect_int.at(i), vect_int.at(store_index));
			++store_index;
		}
	}
	
	//move pivot to its final place
	std::swap(vect_int.at(right), vect_int.at(store_index));
	return store_index;
}


unsigned
getSmallest(IntVector& vect_int, unsigned left, unsigned right, unsigned k)
{
	if (left == right)
		return vect_int.at(left);
	
	unsigned pivot_index = (left + right)/2;	//select a pivot between left and right
	
	//partiton the list: left will contain elements smaller than pivot
	unsigned pivot_newindex = partition(vect_int, left, right, pivot_index);
	
	unsigned pivot_dist = pivot_newindex - left + 1;
	//pivot_dist: how many elements are smaller or equal than pivot
	
	std::cout<<"pivot_index: "<<pivot_index<<" pivot_newindex: "<<pivot_newindex<<" pivot_dist: "<<pivot_dist<<std::endl;
	printVector(vect_int);
	std::cout<<std::endl;
	
	if (pivot_dist ==k)
	{
		return vect_int.at(pivot_newindex);
	}
	
	
	if (k < pivot_dist)	//search the kth element in the first pivot_dist elements
	{
		return getSmallest(vect_int, left, pivot_newindex - 1, k);
	}
	
	return getSmallest(vect_int, pivot_newindex+1, right, k-pivot_dist);
}



int main()
{
	IntVector vect_int = generateVector();
	printVector(vect_int);
	
	unsigned k = vect_int.size()/2;
	//std::cout<<"k: "<<k<<"\n";
	std::cout<<k<<"th element: "<<getSmallest(vect_int, 0, vect_int.size()-1, k)<<"\n";
	printVector(vect_int);
	
	return 0;
}
