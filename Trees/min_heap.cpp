#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "../common/GenVector.hpp"

/* Problem: create min-heap from unsorted array  */

void
insertMinHeap(IntVector& min_heap, unsigned elem)
{
	/* heapify-up:
		Add the element to the bottom level of the heap.
		Compare the added element with its parent; if they are in the correct order, stop.
		If not, swap the element with its parent and return to the previous step.
	*/
	
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

IntVector::value_type
deleteRoot(IntVector& min_heap)
{
	if (min_heap.empty())
	{
		throw std::runtime_error("Empty min-heap");
	}

	/* heapify-down:
		Replace the root of the heap with the last element on the last level.
		Compare the new root with its children; if they are in the correct order, stop.
		If not, swap the element with one of its children and return to the previous step. (Swap with its smaller child in a min-heap and its larger child in a max-heap.)	 
	*/
	
	IntVector::value_type min_val = min_heap.at(0);
	if (min_heap.size() == 1)	//single element
	{
		min_heap.pop_back();	//remove single element
		return min_val;
	}
	
	
	//make last element root
	std::swap(min_heap.at(0), min_heap.at(min_heap.size() - 1));
	//remove root
	min_heap.pop_back();
	
	if (min_heap.size() < 2)
	{
		return min_val;
	}
	
	if (min_heap.size() == 2)
	{
		//2 elements
		if (min_heap.at(0) > min_heap.at(1))
		{
			std::swap(min_heap.at(0), min_heap.at(1));
		}
		return min_val;

	}
	
	std::cout<<"After extracting min:\n";
	printVector(min_heap);
	std::cout<<"Start heapify-down\n";
	
	unsigned cidx = 0;	//current element index
	unsigned ch1 = 2 * cidx + 1;	//first child
	unsigned ch2 = 2 * cidx + 2;	//second child
	
	//min_heap has at least 3 elements
	//compare new root with its children
	while (cidx <= (min_heap.size()/2))
	{
		ch1 = 2 * cidx + 1;
		ch2 = 2 * cidx + 2;
		
		if (ch1 >= min_heap.size())
		{
			return min_val;
		}
		
		if (min_heap.at(cidx) < min_heap.at(ch1))
		{
			if (ch2 >= min_heap.size() || min_heap.at(cidx) < min_heap.at(ch2))
			{
				return min_val;	//everything is OK
			}
			
			//child2 is smaller than parent; swap them
			std::swap(min_heap.at(cidx), min_heap.at(ch2));
			cidx = ch2;
		}
		else
		{
			//get min(child1, child2)
			if (ch2 >= min_heap.size() || min_heap.at(ch1) < min_heap.at(ch2))
			{
				std::swap(min_heap.at(cidx), min_heap.at(ch1));
				cidx = ch1;
			}
			else
			{
				std::swap(min_heap.at(cidx), min_heap.at(ch2));
				cidx = ch2;
			}
		}
		
		printVector(min_heap);
	}
	
	return min_val;
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
		
		IntVector::value_type min_val = deleteRoot(mheap);
		std::cout<<"min_val: "<<min_val<<"\n";
		printVector(mheap);
		checkMinHeap(mheap);
		std::cout<<"-----------------------------------------------------\n";
	}
	
	{
		IntVector vect;
		vect.push_back(20);
		vect.push_back(10);

		IntVector mheap = createMinHeap(vect);
		printVector(mheap);
		checkMinHeap(mheap);
		
		IntVector::value_type min_val = deleteRoot(mheap);
		std::cout<<"min_val: "<<min_val<<"\n";
		printVector(mheap);
		checkMinHeap(mheap);
		std::cout<<"-----------------------------------------------------\n";
	}
	
	{
		IntVector vect;
		vect.push_back(40801);
		vect.push_back(21673);
		vect.push_back(608);

		IntVector mheap = createMinHeap(vect);
		printVector(mheap);
		checkMinHeap(mheap);
		
		IntVector::value_type min_val = deleteRoot(mheap);
		std::cout<<"min_val: "<<min_val<<"\n";
		printVector(mheap);
		checkMinHeap(mheap);
		std::cout<<"-----------------------------------------------------\n";
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
		
		IntVector::value_type min_val = deleteRoot(mheap);
		std::cout<<"min_val: "<<min_val<<"\n";
		printVector(mheap);
		checkMinHeap(mheap);
		std::cout<<"-----------------------------------------------------\n";
	}

	
	{
		IntVector vect = generateVector();
		IntVector mheap = createMinHeap(vect);
		printVector(mheap);
		if (!checkMinHeap(mheap))
		{
			printVector(vect);
		}
		
		IntVector::value_type min_val = deleteRoot(mheap);
		std::cout<<"min_val: "<<min_val<<"\n";
		printVector(mheap);
		checkMinHeap(mheap);
		std::cout<<"-----------------------------------------------------\n";
	}
	
	return 0;
}
