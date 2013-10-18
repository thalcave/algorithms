#include "Random.hpp"

#include <stdlib.h>
#include <stdexcept>

Random::Random()
: gen(time(0))
{
	//unsigned iseed = (unsigned)time(NULL);
	//srand(iseed);
}

unsigned
Random::getRandom(unsigned start, unsigned end)
{
	if (start > end)
	{
		throw std::logic_error("Invalid range, start is bigger than end");
	}
	
	/*//1: generate a random number in range [0, range]
	//2: add start to it
	unsigned range = end - start;
	return start + static_cast<int>((double)rand() / (RAND_MAX+1) * (range+1));*/
	
	boost::uniform_int<> dist(start, end);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);
	return die();
}
