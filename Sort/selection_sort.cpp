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
selectionSort(IntVector& vect_int)
{
    if (vect_int.empty())
    {
	return;
    }

    //find min in vector and move it on start position

    for (IntVector::size_type i = 0; i < vect_int.size() -1 ; ++i)
    {
	unsigned pos = i;
	for (IntVector::size_type j = i + 1; j < vect_int.size(); ++j)
	{
	    if (vect_int.at(pos) > vect_int.at(j))
	    {
		pos = j;
	    }
	}
	
	if (pos != i)
	{
	    unsigned aux = vect_int.at(pos);
	    vect_int.at(pos) = vect_int.at(i);
	    vect_int.at(i) = aux;
	}
    }
}

int main()
{
	IntVector vect_int = generateVector();
	printVector(vect_int);
	selectionSort(vect_int);
	printVector(vect_int);
	return 0;
}
