#include <iostream>
#include <boost/lexical_cast.hpp>

void
testEven(unsigned long number)
{
	std::cout<<number<<" even? "<<(number & 1  ? "no":"yes")<<"\n";
}

/*
 * for 4:
 * 	x = 4 =    100
 * 	x -1 = 3 = 011
 * 	result =   000
 */ 
int isPowerOfTwo (unsigned int x)
{
  return ((x != 0) && !(x & (x - 1)));
}

void
testPowerOf2(unsigned long number)
{
	bool is_power = isPowerOfTwo(number);
	std::cout<<number<<" is power of 2? "<<(is_power ? "yes":"no")<<"\n";
	
	std::cout<<number<<"/2 = "<<(number >> 1) <<"\n";
	std::cout<<number<<"*2 = "<<(number << 1) <<"\n";
}

void
getPower(unsigned long num)
{
	//count the 1 bits
	unsigned long number = num;
	
	unsigned no_bits = 0;	//no of 1 bits
	unsigned pos = 0;	//position of 1 bit
	unsigned cidx = 0;	//current position
	
	while (number && no_bits <= 1)
	{
		if ((number & 1))	//least significat bit is 1
		{
			++no_bits;
			pos = cidx;
		}
		
		++cidx;
		number >>= 1;
	}
	
	if (no_bits == 1)
	{
		std::cout<<num<<" is power of 2: "<<pos<<"\n";
	}
}


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"Usage: ./test_even <number>\n";
		return -1;
	}
	
	unsigned long number(boost::lexical_cast<unsigned long>(std::string(argv[1])));
	
	testEven(number);
	testPowerOf2(number);
	getPower(number);
	
	return 0;
}

