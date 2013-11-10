#include "GenVector.hpp"
#include <iostream>
#include <iterator>
#include <stdlib.h>

IntVector
generateVector(unsigned& searched) 
{
	unsigned iseed = (unsigned)time(NULL);
	srand(iseed);

	//generate size
	unsigned n = 1 + (int) (30.0 * (rand() / (RAND_MAX + 1.0)));
	std::cout<<"size: "<<n<<"\n";

	IntVector vect_int;
	for (unsigned i = 0; i < n; ++i)
	{
		vect_int.push_back(1 + (int)(50000.0 * (rand()/(RAND_MAX + 1.0))));
		//:w
		//std::cout<<"v[i]="<<vect_int.at(i)<<"\n";

	}

	//generate search key
	unsigned spos = 1 + (int) ((n-1) * (rand() / (RAND_MAX + 1.0)));
	std::cout<<"spos: "<<spos<<"\n";
	searched = vect_int.at(spos);
	return vect_int;
}


void
printVector(IntVector const& vint)
{
    std::copy(vint.begin(), vint.end(), std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout<<"\n";
}
