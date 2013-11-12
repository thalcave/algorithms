/**
 * Problem: Find longest increasing sequence
 * Solution: keep a table of intermediate results
 * 	l[i] = longest sequence ending with a[i]
 * 	l[i] = max(l[0], ...l[j]) + 1, where a[j] < a[i]
 * keep also a predecessor table:
 * 	
 */

#include "../common/GenVector.hpp"
#include <iostream>
#include <algorithm>

unsigned
getMaxLength(const IntVector& l, const IntVector& vect_int, unsigned i, std::vector<int>& pred)
{
	unsigned max = 0;
	int pos = -1;
	for (unsigned j = 0; j < i; ++j)
	{
		if (l.at(j) > max && vect_int.at(j) < vect_int.at(i))
		{
			max = l.at(j);
			pos = j;
		}
	}
	
	pred.at(i) = pos;
	
	return max;
}

void
printSequence(const IntVector& vect_int, const std::vector<int>& pred, const IntVector& l)
{
	unsigned max_len = 0;	//sequence with max_len
	unsigned i = 0;
	unsigned end_seq = 0;	//where the max_sequence ends
	for (; i < l.size(); ++i)
	{
		if (max_len < l[i])
		{
			max_len = l[i];
			end_seq = i;
		}
	}
	//display sequence
	std::cout<<"max seq: "<<max_len<<"\n";
	unsigned pidx = end_seq;	//predecessor index
	IntVector tmp;
	tmp.push_back(vect_int.at(pidx));

	while (pred.at(pidx) >= 0)
	{
		tmp.push_back(vect_int.at(pred.at(pidx)));
		pidx = pred.at(pidx);
	}
	
	std::cout<<"Sequence: ";
	for (int i = tmp.size() - 1; i >= 0; --i)
	{
		std::cout<<tmp.at(i)<<" ";
	}
	std::cout<<"\n";
}

void
findLongestSequence(const IntVector& vect_int)
{
	//l[i] = longest sequence ending with a[i]
	IntVector l(vect_int.size(), 1);
	
	std::vector<int> pred(vect_int.size(), -1);	//list of predecessors
	
	for (unsigned i = 0; i < vect_int.size(); ++i)
	{
		//find max from l
		l.at(i) = 1 + getMaxLength(l, vect_int, i, pred);
	}
	
	//std::cout<<"max seq: "<<*std::max_element(l.begin(), l.end())<<"\n";
	printSequence(vect_int, pred, l);
}

int main()
{
	IntVector vect_int = generateVector();
	printVector(vect_int);
	
	findLongestSequence(vect_int);
	
	std::sort(vect_int.begin(), vect_int.end());
	findLongestSequence(vect_int);
	
	std::sort(vect_int.begin(), vect_int.end(), std::greater<unsigned>());
	findLongestSequence(vect_int);

	return 0;
}
