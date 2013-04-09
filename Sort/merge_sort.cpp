#include "GenVector.hpp"
#include <iterator>
#include <iostream>


/*void
printVector(IntVector const& vint)
{
    std::copy(vint.begin(), vint.end(), std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout<<"\n";
}*/

IntVector
merge(IntVector const& left, IntVector const& right)
{
    IntVector res;

    printVector(left);
    printVector(right);

    //merge 2 vectors
    IntVector::const_iterator lit(left.begin());
    IntVector::const_iterator rit(right.begin());
    while (lit != left.end() && rit != right.end())
    {
	if (*lit < *rit)
	{
	    res.push_back(*lit);
	    ++lit;
	    continue;
	}

	if (*rit < *lit)
	{
	    res.push_back(*rit);
	    ++rit;
	    continue;
	}

	res.push_back(*lit);
	res.push_back(*rit);
	++lit;
	++rit;
    }

    if (lit == left.end())
    {
	res.insert(res.end(), rit, right.end());
    } else
    {
	res.insert(res.end(), lit, left.end());
    }
    return res;
    //printVector(left);
    //std::cout<<"piv: "<<pivot<<"\n";
    //printVector(right);
    //std::cout<<"------------------------\n";
    //std::cout<<"###################################\n";

}

IntVector
mergeSort(IntVector& vect_int)
{
    if (vect_int.size() <= 1)
    {
	return vect_int;
    }

    //split vector into 2 subvectors
    IntVector::size_type middle = vect_int.size()/2;

    IntVector left(vect_int.begin(), vect_int.begin() + middle);
    IntVector right(vect_int.begin() + middle , vect_int.end());

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

int main()
{
	IntVector vect_int = generateVector();
	printVector(vect_int);
	IntVector sorted = mergeSort(vect_int);
	printVector(sorted);
	return 0;
}
