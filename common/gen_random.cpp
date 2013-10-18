#include "Random.hpp"

#include <iostream>

int main()
{
	Random rand;
	for (unsigned i = 0; i < 10; ++i)
	{
		std::cout<<rand.getRandom(0, 1000)<<" ";
	}
	
	std::cout<<"\n";
	return 0;
}
