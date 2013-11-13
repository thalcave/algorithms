#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <numeric>
#include <stdexcept>

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

unsigned
getMaxCoin(unsigned n)
{
	IntVector::const_reverse_iterator coin_it(coins.rbegin());
	for (; coin_it != coins.rend(); ++coin_it) 
	{
//		std::cout<<*coin_it<<std::endl;
		if (n >= *coin_it)
		{
			return *coin_it;
		}
	}
	
	throw std::logic_error("Cannot find coin smaller than n");
}

void
computeCoins(unsigned n)
{
	unsigned sum = n;
	while (sum)
	{
		//get max. coin which is smaller than sum
		unsigned max_coin = getMaxCoin(sum);
		
		unsigned count = sum/max_coin;
		//std::cout<<"count: "<<count<<"\n";
		for (unsigned i = 0; i < count; ++i)
		{
			solution.push_back(max_coin);
		}
		
		//std::cout<<"sum: "<<sum <<" max_coin:"<<max_coin<<"\n";
		
		sum = sum%max_coin;
	}
}

unsigned
smallest(unsigned x, unsigned y, unsigned z)
{
    return std::min(std::min(x, y), z);
}

IntVector
getNext(unsigned number)
{
	IntVector result;
	IntVector::const_iterator coin_it(coins.begin());
	for (; coin_it != coins.end(); ++coin_it)
	{
		if (number >= *coin_it)
		{
			result.push_back(number - *coin_it);
		}
		else
		{
			break;
		}
	}
	
	return result;

}

unsigned
computeRecursive(unsigned n)
{
	if (!n)
	{
		return 0;
	}

	//IntVector candidates = getNext(n);
	if (n >= 25)
	{
		return 1 + smallest(computeRecursive(n - 1), computeRecursive(n - 10), computeRecursive(n - 25));
	}
	
	if (n >= 10)
	{
		return 1 + std::min(computeRecursive(n - 1), computeRecursive(n - 10));
	}
	
	if (n >= 1)
	{
		return 1 + computeRecursive(n - 1);
	}
	
	return n;
}

unsigned
getCoin(unsigned i)
{
	//binary_search
	if (std::binary_search(coins.begin(), coins.end(), i))
	{
		//std::cout<<"Found exact coin: "<<i<<"\n";
		return i;
	}
	
	return 0;
}

std::vector<IntVector> dyn_solution;

unsigned
getPreviousMin(IntVector const& s, unsigned i)
{
	//we have to compute min number of coins for i, knowing solution for 0..i-1
	//subtract each coin from i (x = i - coin(j)) and get minimum from s[x]
	unsigned diff = i - coins.at(0);
	if (diff > s.size())
	{
		std::cerr<<"diff: "<<diff<<"\n";
		throw std::logic_error("Invalid diff");
	}
	unsigned min = s.at(diff);	//start with this
	
	unsigned found_coin = 0;
	unsigned prev_idx = diff;
	
	for (unsigned j = 1; j < coins.size(); ++j)
	{
		//std::cout<<"Coin at j :"<<coins.at(j)<<"\n";
		if (i > coins.at(j))
		{
			diff = i - coins.at(j);
			if (diff > s.size())
			{
				std::cerr<<"diff2: "<<diff<<"\n";
				throw std::logic_error("Invalid diff");
			}
			
			if (min > s.at(diff))
			{
				min = s.at(diff);
				found_coin = j;
				prev_idx = diff;
			}
		}
	}
	
	IntVector tmp = dyn_solution.at(prev_idx);
	tmp.push_back(coins.at(found_coin));
	dyn_solution.push_back(tmp);
	
	//std::cout<<"For i: "<<i<<" found min: "<<min<<" at :"<<diff<<"\n";
	//std::cout<<"Found coin: "<<coins.at(found_coin)<<"\n";
	//printVector(tmp);
	return min;
}

/*Dynamic approach:
 * 	s[n] = 	coin[x], if coin[x] == i
 * 		min(s[j]) + 1, where exists a coin[x] = s[i] - s[j]
*/
void
computeDynamic(unsigned n)
{
	IntVector s;	//s[n] = how many coins do we need to compute n
	s.push_back(0);	//0 coins for 0
	dyn_solution.push_back(IntVector());
	
	for (unsigned i = 1; i <= n; ++i)
	{
		unsigned coin = getCoin(i);
		if (coin)	//found a coin equal to i
		{
			s.push_back(1);
			dyn_solution.push_back(IntVector(1, coin));
		}
		else
		{
			coin = getPreviousMin(s, i);
			if (!coin)
			{
				std::cerr<<"i: "<<i<<"\n";
				throw std::logic_error("Cannot find a coin for current i");
			}
			s.push_back(coin + 1);
		}
	}
	
	printVector(dyn_solution.back());
	//printVector(s);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"Usage: ./coin <number>\n";
		return -1;
	}
	
	coins.push_back(1);
	//coins.push_back(2);
	//coins.push_back(5);
	coins.push_back(10);
	coins.push_back(25);
	std::sort(coins.begin(), coins.end());
	
	unsigned long number = boost::lexical_cast<unsigned long>(std::string(argv[1]));
	
	if (number < 25)
	{
		clock_t ticks = clock();
		IntVector cset;
		generateBacktrack(cset, number);
		printVector(solution);
		std::cout << "Back: "<< clock() - ticks << std::endl;
	}
	
	{
		//not working good
		solution.clear();
		computeCoins(number);
		std::cout<<"Greedy: ";
		printVector(solution);
	}
	
	if (number < 100)
	{	//another solution
		//change(n)= 1+ min({change(n-1),change(n-2),change(n-5)})
		solution.clear();
		unsigned n = computeRecursive(number);
		std::cout<<"recursive n: "<<n<<"\n";
	}
	
	{
		solution.clear();
		computeDynamic(number);
	}
	return 0;
}
