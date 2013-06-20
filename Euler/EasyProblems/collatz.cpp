#include <iostream>
#include <map>
#include <unordered_map>
/*

Euler 14

The following iterative sequence is defined for the set of positive integers:

n --> n/2 (n is even)
n -->  3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

13  -->  40  -->  20  -->  10  -->  5  -->  16  -->  8  -->  4  -->  2  -->  1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. 
Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
*/

//hold in map associations number --> sequence length
typedef std::unordered_map<unsigned, unsigned> MapNoSeq;
typedef std::unordered_map<unsigned, unsigned>::const_iterator MapConstIt;
MapNoSeq seq_lens;

const unsigned START = 999999;

//returns 0 if number is not power of 2, otherwise it returns the power
unsigned
getPowerOf2(unsigned num)
{
	//count the 1 bits
	unsigned number = num;
	
	unsigned no_bits = 0;	//no of 1 bits
	unsigned pos = 0;	//position of 1 bit
	unsigned cidx = 0;	//current position
	
	while (number && no_bits <= 1)
	{
		if ((number & 1))	//least significant bit is 1
		{
			++no_bits;
			pos = cidx;
		}
		
		++cidx;
		number >>= 1;
	}
	
	return no_bits == 1 ? pos : 0;
}


unsigned
getSequence(unsigned number)
{
	unsigned cnum = number;
	unsigned step = 0;
	
	while (cnum > 1)
	{
		MapConstIt found = seq_lens.find(cnum);
		if (found != seq_lens.end())
		{
			//insert number with sequence length
			unsigned clen = step + found->second;
			seq_lens[number] = clen;
			
			//std::cout<<"inserted "<<number<<" with len: "<<clen<<"\n";
			//std::cout<<"found number: "<<cnum<<"\n";
			
			return clen;
		}
		
		//check if number is odd or even
		if (cnum & 1)	//odd
		{
			cnum = 3 * cnum + 1;
		}
		else
		{
			//it's even, see if it's power of 2 --not a real optimization
			/*unsigned power_2 = getPowerOf2(cnum);
			if (power_2)
			{
				unsigned clen = step + power_2 + 1;
				seq_lens[number] = clen;
			
				//std::cout<<"inserted "<<number<<" with len: "<<clen<<" step: "<<step <<" cnum: "<<cnum<<"\n";
				return clen;
			}*/
			
			//division by 2
			cnum >>= 1;
		}
		
		++step;
	}
	
	++step;
	seq_lens[number] = step;
	//std::cout<<"inserted2 "<<number<<" with len: "<<step<<"\n";
	
	return step;
}

int main()
{
	unsigned max_seq = 0;
	unsigned number = 0;

	//for (unsigned idx = START; idx > 0; --idx)
	for (unsigned idx = 1; idx <= START; ++idx)	//better to start bottom-up
	{
		unsigned res = getSequence(idx);
		if (res > max_seq)
		{
			max_seq = res;
			number = idx;
		}
	}
	
	std::cout<<"max seq is: "<<max_seq<<" for : "<<number<<"\n";
	std::cout<<"map size: "<<seq_lens.size()<<"\n";
	
	
	return 0;
}
