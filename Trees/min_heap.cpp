#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "../common/GenVector.hpp"

/* Problem: create min-heap from unsorted array  */

void
insertMinHeap(IntVector& min_heap, unsigned elem)
{
	//std::cout<<"push at end: "<<elem<<"\n";
	//add elem at end
	min_heap.push_back(elem);
	
	//check if parent is smaller than elem
	unsigned cidx = min_heap.size() - 1;
	//parent idx
	unsigned pidx = (cidx-1)/2;

	//if parent is greater than children, swap them
	while (min_heap.at(pidx) > min_heap.at(cidx))
	{
		std::swap(min_heap.at(pidx), min_heap.at(cidx));
		
		//current elem is swapped with parent, check again new parent
		cidx = pidx;		//index of current elem is index of former parent
		if (!cidx)
		{
			return;
		}
		pidx = (cidx-1)/2;	//new parent
		
		
		printVector(min_heap);
	}
	
	return;

}

IntVector
createMinHeap(const IntVector& vect)
{
	/* a min heap is a binary heap with < comparison
	 * 	binary heap: binary tree that
	 * 		is complete: all levels of tree are filled (except possibly the last one)
	 * 		all nodes are less (greater than) each of its children
	*/
	
	IntVector min_heap;
	IntVector::const_iterator vect_it(vect.begin());
	min_heap.push_back(*vect_it);
	++vect_it;
	
	for (; vect_it != vect.end(); ++vect_it)
	{
		//insert current element
		insertMinHeap(min_heap, *vect_it);
	}
	
	return min_heap;
}

bool
checkMinHeap(const IntVector& vect)
{
	unsigned i =0;
	for (; i < vect.size();++i)
	{
		unsigned chld1 = 2 * i + 1;
		unsigned chld2 = 2 * i + 2;
		
		if (chld1 < vect.size() && vect.at(i) > vect.at(chld1))
		{
			std::cout<<"Parent("<<i<<") : "<<vect.at(i) << " is bigger than child("<<chld1<<"): "<<vect.at(chld1)<<"\n";
			return false;
		}
		if (chld2 < vect.size() && vect.at(i) > vect.at(chld2))
		{
			std::cout<<"Parent("<<i<<") : "<<vect.at(i) << " is bigger than child("<<chld2<<"): "<<vect.at(chld2)<<"\n";
			return false;
		}
	}
	
	return true;
}

int main()
{
	//IntVector vect = generateVector();
	{
		IntVector vect(1, 10);
		IntVector mheap = createMinHeap(vect);
		printVector(mheap);
		checkMinHeap(mheap);
	}
	
	{
		IntVector vect;
		vect.push_back(20);
		vect.push_back(10);

		IntVector mheap = createMinHeap(vect);
		printVector(mheap);
		checkMinHeap(mheap);
	}
	
	{
		IntVector vect;
		vect.push_back(46177);
		vect.push_back(14582);
		vect.push_back(38135);
		vect.push_back(32336);
		vect.push_back(35278);
		vect.push_back(12609);
		vect.push_back(16329);
		vect.push_back(34662);
		vect.push_back(48870);
		vect.push_back(39535);
		vect.push_back(13390);
		vect.push_back(45363);
		vect.push_back(23283);
		vect.push_back(10505);
		vect.push_back(15796);
		vect.push_back(2093);
		vect.push_back(20798);
		vect.push_back(2713);
		vect.push_back(45734);
		vect.push_back(35714);
		vect.push_back(10370);
		vect.push_back(39899);
		vect.push_back(12804);
		vect.push_back(28767);
		vect.push_back(28556);
		vect.push_back(5317);
		vect.push_back(19653);
		vect.push_back(8762);
		vect.push_back(6644);
		vect.push_back(11987);
		IntVector mheap = createMinHeap(vect);
		printVector(mheap);
		checkMinHeap(mheap);
	}

	
	{
		IntVector vect = generateVector();
		IntVector mheap = createMinHeap(vect);
		printVector(mheap);
		if (!checkMinHeap(mheap))
		{
			printVector(vect);
		}
	}
	
	return 0;
}
