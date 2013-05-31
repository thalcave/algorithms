#include <iostream>
#include <string>
#include <stdexcept>

/*
 * Euler Problem 8
 * Find the greatest product of five consecutive digits in the 1000-digit number.
73167176531330624919225119674426574742355349194934
96983520312774506326239578318016984801869478851843
85861560789112949495459501737958331952853208805511
12540698747158523863050715693290963295227443043557
66896648950445244523161731856403098711121722383113
62229893423380308135336276614282806444486645238749
30358907296290491560440772390713810515859307960866
70172427121883998797908792274921901699720888093776
65727333001053367881220235421809751254540594752243
52584907711670556013604839586446706324415722155397
53697817977846174064955149290862569321978468622482
83972241375657056057490261407972968652414535100474
82166370484403199890008895243450658541227588666881
16427171479924442928230863465674813919123162824586
17866458359124566529476545682848912883142607690042
24219022671055626321111109370544217506941658960408
07198403850962455444362981230987879927244284909188
84580156166097919133875499200524063689912560717606
05886116467109405077541002256983155200055935729725
71636269561882670428252483600823257530420752963450
 */

/**
 * algorithm to detect 5 consecutive digits who produce the largest product
 * 1. find first sequence of 5 digits not containing 0
 * 2. compute product
 * 3. move to next elem
 * 4. if next elem == 0
 * 		go to #1
 * 	else
 * 		if next_elem < prev_elem
 * 			go to #3
 * 		else
 * 			go to #2
 * 
 */

const int ZERO_DIGIT = '0';
typedef std::string::size_type Index;


//searches first valid sequence (not containing zeroes) from start+offset
//
bool
findValidSequence(std::string const& large_number, Index& start, Index len, Index offset)
{
	do
	{
		if (start + 5 > len)
			return false;

		unsigned i = offset;
		for (; i < 5; ++i)
		{	
			//std::cout<<"ch: "<<large_number.at(start + i)<<"\n";
			if (large_number.at(start + i) == '0')
			{
				start += i + 1;
				break;
			}
		}
		
		if (5 == i)
		{
			break;
		}
		
	} while (true);
	
	return true;
}

unsigned
getProduct(std::string const& large_number, Index start, Index len)
{
	if (start >= len)
	{
		std::cerr<<"Invalid start idx: "<<start<<" len of string: "<<len<<"\n";
		throw std::logic_error("called with invalid index");
	}
	
	unsigned product = 1;
	for (unsigned i = 0; i < 5; ++i)
	{
		product *= (large_number.at(start + i) - 48);
	}
	
	return product;
	
}

unsigned
largest_product(std::string const& large_number)
{
	std::string::size_type len = large_number.length();
	unsigned product = 0;
	
	unsigned max_product = 0;
	Index max_start = 0;
	
	if (len < 5)
	{
		return product;
	}
	
	//we'll work with chars, to avoid conversions string int
	Index start = 0;
	Index offset = 0;	//number of good digits already in sequence; find should start at start+offset, to optimize the search
	unsigned counter = 0;	//how many multiplications were made
	while (start < len)
	{
		//find first sequence of 5 digits not containing 0
		bool found = findValidSequence(large_number, start, len, offset);
		if (!found)
		{
			std::cout<<"No other valid sequence found\n";
			break;
		}
		
		//std::cout<<"valid sequence! start: "<<start<<"\n";
		
		//product = getProduct(large_number, start, len);
		int a = large_number.at(start);
		int b = large_number.at(start+1);
		int c = large_number.at(start+2);
		int d = large_number.at(start+3);
		int e = large_number.at(start+4);
		
		product = (a-48)*(b-48)*(c-48)*(d-48)*(e-48);
		++counter;
		if (product > max_product)
		{
			std::cout << "Interim: "<< start <<" sequence: "<<large_number.substr(start, 5)<<" product: "<<product<<"\n";
			max_product = product;
			max_start = start;
		}
		
		if (start + 5 >= len)	//end of string
		{
			break;
		}
		
		int next_ch = large_number.at(start + 5);
		//std::cout<<"next_ch: "<<next_ch<<"\n";
		if (next_ch == ZERO_DIGIT)	//no use to move to next char; search new valid sequence
		{
			start += 6;
			offset = 0;
			
			//std::cout<<"next_ch IS ZERO \n";
		}
		else
		{
			if (next_ch <= a)	//product b * c * d * e * next_ch  will be smaller than current product
			{
				start += 2;
				offset = 4;
				//std::cout<<"next_ch "<<next_ch << " is smaller than "<<a <<"\n";
			}
			else
			{
				++start;
				offset = 5;
			}
			
		}
	}
	
	std::cout << "Start of biggest sequence: "<< max_start <<" sequence: "<<large_number.substr(max_start, 5)<<"\n";
	std::cout << "No. of multiplications "<<counter<<"\n";
	
	return max_product;
}


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"Usage: ./lrg_product <number>\n";
		return -1;
	}
	
	std::string large_number(argv[1]);
	std::cout<<"Largest product: "<<largest_product(large_number)<<"\n";
	
	return 0;
}

