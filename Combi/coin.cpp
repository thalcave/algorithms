#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <numeric>

/*
 * Problem: Given a set of coin denominators, find the minimum number of coins to make a certain amount of change.
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

IntVector coins, solution;
unsigned cmin = (-1);


void
processSolution(IntVector const& subset)
{
	if (subset.size() < cmin)
	{
		cmin = subset.size();
		solution.assign(subset.begin(), subset.end());
	}
	//printVector(subset);
}


IntVector
getCandidates(IntVector const& cset, unsigned n, unsigned csum)
{
	unsigned diff = n - csum;
	IntVector result;
	for (unsigned i = 0; i < coins.size(); ++i)
	{
		if (coins[i] <= diff)
		{
			result.push_back(coins[i]);
			//diff -= coins[i];
		}
		else
		{
			break;
		}
	}
	
	return result;
}

void
generateBacktrack(IntVector& current_set, unsigned n)
{
	unsigned csum = std::accumulate(current_set.begin(), current_set.end(), 0);
	if (csum > n)
	{
		//discard this solution
		return;
	}
	
	
	if (csum == n)		//if solution, print it
	{
		processSolution(current_set);
	}
	else
	{
		IntVector candidates = getCandidates(current_set, n, csum);
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
		std::cerr<<"Usage: ./coin <number>\n";
		return -1;
	}
	
	coins.push_back(1);
	coins.push_back(2);
	coins.push_back(5);
	coins.push_back(10);
	
	unsigned long number = boost::lexical_cast<unsigned long>(std::string(argv[1]));
	{
		clock_t ticks = clock();
		IntVector cset;
		generateBacktrack(cset, number);
		printVector(solution);
		std::cout << "Back: "<< clock() - ticks << std::endl;
	}
	
	return 0;
}
