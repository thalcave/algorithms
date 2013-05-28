#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>

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
