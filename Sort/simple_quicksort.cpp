#include "../common/GenVector.hpp"
#include <iterator>
#include <iostream>
#include <stdexcept>


/*void
printVector(IntVector const& vint)
{
    std::copy(vint.begin(), vint.end(), std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout<<"\n";
}*/

IntVector
concatenate(IntVector const& left, unsigned pivot, IntVector const& right)
{
    IntVector res;
    //printVector(left);
    //std::cout<<"piv: "<<pivot<<"\n";
    //printVector(right);
    //std::cout<<"------------------------\n";
    res.assign(left.begin(), left.end());
    res.push_back(pivot);
    res.insert(res.end(), right.begin(), right.end());

    //printVector(res);
    //std::cout<<"###################################\n";
    return res;
}

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


void
inPlaceQuickSort(IntVector& vect_int, unsigned left, unsigned right)
{
	if (left >= right)
	{
		return;
	}
	
	IntVector::size_type pivot = (left + right)/2;
	unsigned piv_new_idx = partition(vect_int, left, right, pivot);
	//std::cout<<"new idx: "<<piv_new_idx<<"\n";
	
	if (!piv_new_idx)
	{
		return;
	}
	
	inPlaceQuickSort(vect_int, left, piv_new_idx - 1);
	inPlaceQuickSort(vect_int, piv_new_idx + 1, right);
	
}

IntVector
simpleQuickSort(IntVector& vect_int)
{
    if (vect_int.size() <= 1)
    {
	return vect_int;
    }

    //pick pivot from list
    //smaller elems go to minlist
    //greater elems go to maxlist
    IntVector::size_type pivot = vect_int.size()/2;
    unsigned piv_value = vect_int.at(pivot);
    
    vect_int.erase(vect_int.begin() + pivot);

    IntVector min_vect, max_vect;

    for (IntVector::size_type i = 0; i < vect_int.size(); ++i)
    {
	if (vect_int.at(i) < piv_value)
	{
	    min_vect.push_back(vect_int.at(i));
	}
	else
	{
	    max_vect.push_back(vect_int.at(i));
	}
    }

    //std::cout<<"pivot= "<<piv_value<<"\n";
    //printVector(min_vect);
    //printVector(max_vect);

    return concatenate(simpleQuickSort(min_vect), piv_value, simpleQuickSort(max_vect));
}

int main()
{
	IntVector vect_int = generateVector();
	printVector(vect_int);
	
	IntVector tmp(vect_int);
	IntVector sorted = simpleQuickSort(tmp);
	printVector(sorted);
	
	inPlaceQuickSort(vect_int, 0, vect_int.size() - 1);
	printVector(vect_int);
	
	return 0;
}
