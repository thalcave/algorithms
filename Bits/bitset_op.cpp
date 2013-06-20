#include <iostream>
#include <boost/lexical_cast.hpp>
#include <bitset>

void
testEven(const std::bitset<32>& number)
{
	std::cout<<number.to_ulong()<<" even? "<<(number[0]==0 ? "yes":"no")<<"\n";
}

void
testPowerOf2(const std::bitset<32>& number)
{
	//this works
	std::cout<<number.to_ulong()<<" power of 2? "<<(number.count()==1 ? "yes":"no")<<"\n";
	
	//we can manually count the bits
	bool is_power = false;
	unsigned pos = 0;	//pos of bit 1
	for (unsigned i = 0; i < number.size(); ++i)
	{
		if (number.test(i))
		{
			if (pos)	//already found a 1 bit
			{
				is_power = false;
				break;
			}
			
			is_power = true;
			pos = i;
		}
	}
	
	if (is_power)
	{
		std::cout<<number.to_ulong()<<" power of 2 = "<<pos<<"\n";	
	}
}


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"Usage: ./test_even <number>\n";
		return -1;
	}
	
	std::bitset<32> number(boost::lexical_cast<unsigned long>(std::string(argv[1])));;
	
	testEven(number);
	testPowerOf2(number);
	
	return 0;
}

