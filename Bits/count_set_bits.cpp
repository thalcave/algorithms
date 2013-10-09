#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <stdexcept>
#include <fstream>
#include <string.h>
#include <errno.h>
#include <boost/algorithm/string.hpp>
#include <vector>

/**
 * 
 *
How to count the number of set bits in a 32-bit integer array?

#1 compute some lookup tables: number --> no. of bits set
#2 for each number (32-bits):
	separate in 4 * 8 bits number
	add no. of bits set
 */

std::vector<unsigned> bits_lookup;

std::vector<unsigned> numbers;
	


unsigned
get_no_bits(unsigned number)
{
	//std::cout<<"number: "<<number<<" ";
	
	unsigned no_bits = 0;
	while (number)
	{
		if (number & 1)	//lst bit is 1
		{
			++no_bits;
		}
		
		number >>= 1;	//right shift with 1 bit
	}
	
	//std::cout<<"no_bits: "<<no_bits<<"\n";
	
	return no_bits;
}

void
comnputeLookupTable()
{
	for (unsigned i = 0; i < 256; ++i)
	{
		bits_lookup.push_back(get_no_bits(i));
	}
}

unsigned
convertString(std::string const& str)
{
	//std::cout <<str<< " + ";
	try
	{
		unsigned nr = boost::lexical_cast<unsigned>(str);
        } catch(boost::bad_lexical_cast const& bc) {
                std::cout<<"caught error: "<<bc.what()<<" str: "<<str<<"\n";
		throw;
        }
	
}


void
readNumbers(std::string const& input_file)
{
	std::ifstream input(input_file.c_str());
	if (!input.good())
	{
		throw std::runtime_error("Error opening file: " + input_file + "; reason: " + std::string(strerror(errno)));
	}
	
	char buffer[33];
	
	while (input.getline(buffer, 33).good())
	{
		//read line by line
		numbers.push_back(convertString(buffer));
	}
	
	input.close();
	
	std::cout<<"Read: "<<numbers.size()<<" numbers\n";
}

void
countBits()
{
	unsigned long no_bits = 0;
	std::vector<unsigned>::const_iterator it(numbers.begin());
	clock_t ticks = clock();
	for (; it != numbers.end(); ++it)
	{
		no_bits += get_no_bits(*it);
	}
        std::cout << "counted "<<no_bits<<" bits in "<< clock() - ticks << std::endl;
}

void
countBitsLookupTable()
{
	unsigned long no_bits = 0;
	std::vector<unsigned>::const_iterator it(numbers.begin());
	clock_t ticks = clock();
	for (; it != numbers.end(); ++it)
	{
		unsigned cnumber = *it;
		while (cnumber)
		{
			unsigned low8bits = cnumber & 0xFF;
			no_bits += bits_lookup[low8bits];
			cnumber >>=8;
		}
		
	}
        std::cout << "counted "<<no_bits<<" bits in "<< clock() - ticks << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"Usage: ./count_bits <input_file>\n";
		return -1;
	}
	
	std::string input_file(argv[1]);
	readNumbers(input_file);
	
	comnputeLookupTable();
	
	countBits();
	countBitsLookupTable();
	
	return 0;
}
