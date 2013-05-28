#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <math.h>
#include <stdlib.h>

bool
isPrime(unsigned long number)
{
	if (number <=1)
		return false;
	
	unsigned long sqr_root = sqrt(number) + 1;
	
	for (unsigned long i = 2; i < sqr_root; ++i)
	{
		if  (!(number % i))
		{
			return false;
		}
	}
	
	return true;
}

unsigned long
largest_prime_factor(unsigned long number)
{
	//prime factor = prime number which divides an integer exactly
	unsigned long limit = number/2;
	
	unsigned long idx = 2;
	
	ldiv_t result = {0};
	
	while (idx <= limit)
	{
		//std::cout<<"idx: "<<idx<<"\n";
		result = ldiv(number, idx);
		if (!result.rem && isPrime(result.quot))
		{
			return result.quot;
		}
		++idx;
	}
	
	return 0;
}


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"Usage: ./lrg_pf <number>\n";
		return -1;
	}
	
	unsigned long number = boost::lexical_cast<unsigned long>(std::string(argv[1]));
	std::cout<<"Largest prime factor: "<<largest_prime_factor(number)<<"\n";
	
	return 0;
}