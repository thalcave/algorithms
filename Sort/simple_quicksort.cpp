#include "../common/GenVector.hpp"
#include <iterator>
#include <iostream>


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
	IntVector sorted = simpleQuickSort(vect_int);
	printVector(sorted);
	return 0;
}
