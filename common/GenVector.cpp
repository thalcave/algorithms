#include "GenVector.hpp"
#include <iostream>
#include <iterator>
#include <stdlib.h>

#include "Random.hpp"

IntVector
generateVector() 
{
	Random rand;
	
	//generate size
	unsigned n = rand.getRandom(1, 30);
	//unsigned n = 1 + (int) (30.0 * (rand() / (RAND_MAX + 1.0)));
	std::cout<<"size: "<<n<<"\n";

	IntVector vect_int;
	for (unsigned i = 0; i < n; ++i)
	{
		//vect_int.push_back(1 + (int)(50000.0 * (rand()/(RAND_MAX + 1.0))));
		vect_int.push_back(rand.getRandom(0, 50000));

	}
	return vect_int;
}


void
printVector(IntVector const& vint)
{
    std::copy(vint.begin(), vint.end(), std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout<<"\n";
}
