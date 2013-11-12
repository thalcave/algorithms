#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <stack>

/*
 * Problem: generate all subsets of S = {0..N}
 * Solution: use a bitset
 * Solution: use backtracking
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
processSolution(IntVector const& subset)
{
	//printVector(subset);
}


IntVector
getCandidates(IntVector const& current, unsigned n)
{
	//from S = {1 ..n}, return those elements which are not in current
	/*
	 * for i = 1 to n
	 * 	search i in current
	 * 	if not found --> add it to result
	 * O(n * m)...try something better: O(n+m)
	 */
	
	//initialize a vector with n zero elements
	IntVector tmp(n, 0), result;
	for (unsigned i = 0; i < current.size(); ++i)	//O(m)
	{
		tmp.at(current.at(i)) = 1;
	}
	
	for (unsigned i = 0; i < n; ++i)		//O(n)
	{
		if (!tmp.at(i))
		{
			result.push_back(i);
		}
	}
	
	return result;
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
		IntVector candidates = getCandidates(current_set, n);
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
		std::cerr<<"Usage: ./perms <number>\n";
		return -1;
	}
	
	unsigned long number = boost::lexical_cast<unsigned long>(std::string(argv[1]));
	{
		clock_t ticks = clock();
		IntVector cset;
		generateBacktrack(cset, number+1);
		std::cout << "Back: "<< clock() - ticks << std::endl;
	}
	
	return 0;
}
