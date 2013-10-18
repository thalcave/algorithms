#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>


class Random
{
public:
	Random();
	
	//returns random number in interval [start, end]
	unsigned getRandom(unsigned start, unsigned end);
private:
	boost::mt19937 gen;
};



#endif
