#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <boost/lexical_cast.hpp>

/*
 * 
 * decompose a number in prime factors
*/

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

unsigned
getPrimeFactors(unsigned long number)
{
	//prime factor = prime number which divides an integer exactly
	unsigned long limit = number/2;
	
	unsigned long idx = 2;
	
	ldiv_t result = {0};
	
	while (idx <= limit)
	{
		if (isPrime(idx))
		{
			unsigned power = 0;
			result = ldiv(number, idx);
			while (!result.rem)
			{
				++power;
				result = ldiv(result.quot, idx);
			}
			
			if (power)
			{
				std::cout <<" PFD: "<<idx << " power: "<<power<<"\n";
			}
		}
		++idx;

	}
	
	return 0;
}

int main(int argc, char* argv[])
{
        if (argc != 2)
        {
                std::cerr<<"Usage: ./gpf <number>\n";
                return -1;
        }

        unsigned long number = boost::lexical_cast<unsigned long>(std::string(argv[1]));
	getPrimeFactors(number);

        return 0;
}
