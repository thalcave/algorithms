#include <vector>
#include <map>
#include <iostream>

//Problem: given a number K and a vector, find all pairs from vector which sums to value K

void
getPairs(std::vector<int> v, long int k)
{
	//values from v, for later retrieval
	std::map<int, unsigned> vmap;
	for (unsigned i = 0; i < v.size(); ++i)
	{
		vmap.insert(std::make_pair(v.at(i), i));
	}

	//now iterate through vector
	for (unsigned i = 0; i < v.size(); ++i)
	{
		if (v.at(i) > k)
			continue;

		int val = k - v.at(i);

		std::map<int, unsigned>::const_iterator found_it(vmap.find(val));
		
		if (found_it != vmap.end())
		{
			std::cout<<"pair: {"<<v.at(i)<<" , "<<v.at(found_it->second)<<"}\n";
		}
	}
}

/* 2nd approach: 
 * 	- sort vector
 * 	- keep indices for start, end
 * 	- if start + end = K --> found; ++start; --end;
 * 	- if start + end < K --> ++start
 * 	- if start + end > K --> --end
*/

int main()
{
	std::vector<int> vect_int;
	vect_int.push_back(3);
	vect_int.push_back(4);
	vect_int.push_back(5);
	vect_int.push_back(1);
	vect_int.push_back(4);
	vect_int.push_back(2);

	getPairs(vect_int, 6);

	return 0;
}
