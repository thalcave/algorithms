#include <iostream>
#include <boost/lexical_cast.hpp>
#include <bitset>
#include <vector>

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
	
	{
		typedef std::bitset<1> Bit;
		typedef std::vector<Bit> BitArray;
		BitArray bit_array(256,0);
		std::vector<unsigned> vect_int(256,1000);
		
		bit_array.at(1)[0] = 1;
		unsigned idx = 0;
		for (BitArray::const_iterator vit = bit_array.begin(); vit != bit_array.end(); ++vit, ++idx)
		{
			std::cout<<"Bit at : "<<idx<<" is";
			if (vit->test(0))
			{
				std::cout<<" SET\n";
			}
			else
			{
				std::cout<<" not set\n";
			}
		}
		
		std::cout<<"sizeof(bit_array): "<<sizeof(bit_array)<<std::endl;
		std::cout<<"sizeof(vect_int): "<<sizeof(vect_int)<<std::endl;
	}
	
	return 0;
}

