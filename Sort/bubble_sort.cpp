#include "../common/GenVector.hpp"
#include <iterator>
#include <iostream>


/*void
printVector(IntVector const& vint)
{
    std::copy(vint.begin(), vint.end(), std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout<<"\n";
}*/

void
bubbleSort(IntVector& vect_int)
{
    if (vect_int.empty())
    {
	return;
    }

    //iterate through array
    //compare adjacent elems and swap them if needed

    bool sorted = false;
    while (!sorted)
    {
	for (IntVector::size_type i = 0; i < vect_int.size() -1 ; ++i)
	{
	    sorted = true;
	    for (IntVector::size_type j = i + 1; j < vect_int.size(); ++j)
	    {
		if (vect_int.at(i) > vect_int.at(j))
		{
		    std::swap(vect_int.at(i), vect_int.at(j));
		    sorted = false;
		}
	    }
	}
    }
}

int main()
{
	IntVector vect_int = generateVector();
	printVector(vect_int);
	bubbleSort(vect_int);
	printVector(vect_int);
	return 0;
}
