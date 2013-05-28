/*
 * A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91  99.
Find the largest palindrome made from the product of two 3-digit numbers.
*/

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <set>

std::set<unsigned long> computed_values;

bool
isPalindrome(unsigned long number)
{
	//convert this number to string
	std::string converted = boost::lexical_cast<std::string>(number);
	
	unsigned middle = converted.length()/2;
	unsigned str_len = converted.length();
	
	for (unsigned idx = 0; idx < middle; ++idx)
	{
		if (converted.at(idx) != converted.at(str_len - idx - 1))
			return false;
	}
	
	return true;
}

unsigned long
getMaxPal(unsigned start, unsigned min_limit, unsigned long maxpal)
{
	for (unsigned idx = start; idx >= min_limit; --idx)
	{
		unsigned long current_res = start * idx;
		if (computed_values.find(current_res) != computed_values.end())
		{
			continue;	//this was already computed
		}
		
		computed_values.insert(current_res);

		if (current_res < maxpal)	//if current result is smaller than maxpal, no use to continue
		{
			return 0;
		}
			
		if (isPalindrome(current_res))
		{
			return current_res;
		}
	}
	
	return 0;
}

unsigned long
bigPal(unsigned digits_no)
{
	//unsigned long max_no = pow(10, digits_no);
	unsigned long start_range = 1;
	for (unsigned i = 0; i < digits_no-1; ++i)
	{
		start_range *= 10;
	}
	
	unsigned long end_range = start_range * 10 -1;
	
	
	//start from end_range, multiply numbers and check if result is palindrome
	unsigned cstart = end_range;
	unsigned long max_pal = 0;
	
	while (cstart > start_range)
	{	
		//std::cout<<"cstart: "<<cstart<<"\n";
		unsigned long cpal = getMaxPal(cstart, start_range, max_pal);
		if (cpal && max_pal < cpal)
		{
			max_pal = cpal;
		}
		--cstart;
	}
	
	std::cout<<"range: "<<start_range<<", "<<end_range<<"\n";
	
	
	//unsigned current_pal = 99999;
	//std::cout<<current_pal<<" is palindrome? "<< (isPalindrome(current_pal) ? " yes\n" : " no\n");
	
	
	return max_pal;
}

int main(int argc, char* argv[])
{
        if (argc != 2)
        {
                std::cerr<<"Usage: ./bigpal <number_digits>\n";
                return -1;
        }

        unsigned long number = boost::lexical_cast<unsigned long>(std::string(argv[1]));
	std::cout<<"biggest palindrome: "<<bigPal(number)<<"\n";

        return 0;
}
