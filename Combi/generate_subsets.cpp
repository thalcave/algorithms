#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <vector>
#include <iostream>

/*
 * Problem: generate all subsets of S = {0..N}
 * Solution: use a bitset
 */

typedef std::vector<unsigned> IntVector;

void
printVector(IntVector const& subset)
{
	std::cout<<"{";
	for (IntVector::const_iterator vect_it(subset.begin()); vect_it != subset.end(); ++vect_it)
	{
		std::cout<<*vect_it<<" ";
	}
	std::cout<<"}\n";
}

void
generateSubsets(unsigned number)
{
	IntVector set;
	for (unsigned i = 0; i <= number; ++i)
	{
		set.push_back(i);
	}
	
	printVector(set);
	
	unsigned limit = (1 << (number+1)) - 1;
	for (unsigned i = 0; i <= limit; ++i)
	{
		IntVector current_set;
		unsigned cnum = i;
		unsigned count = 0;
		
		//std::cout<<"Process: "<<i<<"\n";
		while (cnum)
		{
			if (cnum & 0x1)	//last bit is set
			{
				current_set.push_back(set.at(count));
			}
			cnum >>= 1;	//right shift one bit
			++count;
		}
		
		printVector(current_set);
	}
}

void
processSolution(IntVector const& subset)
{
	std::cout<<"{";
	for (unsigned i =0; i < subset.size(); ++i)
	{
		if (subset.at(i))
		{
			std::cout<<i<<" ";
		}
	}
	std::cout<<"}\n";
}


void
generateBacktrack(IntVector& current_set, unsigned n)
{
	if (current_set.size() == n)		//if solution, print it
	{
		processSolution(current_set);
	}
	else
	{
		IntVector candidates;
		candidates.push_back(0);
		candidates.push_back(1);
		for (unsigned i =0; i < candidates.size(); ++i)
		{
			current_set.push_back(candidates.at(i));
			generateBacktrack(current_set, n);
			current_set.pop_back();
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"Usage: ./gen_subsets <number>\n";
		return -1;
	}
	
	unsigned long number = boost::lexical_cast<unsigned long>(std::string(argv[1]));
	generateSubsets(number);
	
	
	std::cout<<"Backtracking\n";
	IntVector cset;
	generateBacktrack(cset, number+1);
	
	
	return 0;
}
