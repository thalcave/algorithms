/**
 * Problem: get top 5 elements of an array
 * Solution: keep a set of 5 elements
 */

#include "../common/GenVector.hpp"
#include <set>
#include <iostream>

void
checkInt(IntVector::value_type no, std::multiset<IntVector::value_type>& set_int)
{
	std::cout<<"---------------\n";
	if (set_int.size() < 5)
	{
		std::cout<<"Elem : "<<no<<" inserted\n";
		set_int.insert(no);
		return;
	}
	
	if (*set_int.begin() < no)
	{
		std::cout<<"Elem : "<<*set_int.begin()<<" deleted\n";
		std::cout<<"Elem : "<<no<<" inserted\n";
		set_int.erase(set_int.begin());
		set_int.insert(no);
	}
}

int main()
{
	IntVector vect_int = generateVector();
	printVector(vect_int);
	
	std::multiset<IntVector::value_type> set_int;
	
	IntVector::const_iterator vect_it(vect_int.begin());
	for (; vect_it != vect_int.end(); ++vect_it)
	{
		checkInt(*vect_it, set_int);
	}
	
	std::cout<<"Top 5 : ";
	std::set<IntVector::value_type>::const_iterator set_it(set_int.begin());
	for (; set_it != set_int.end(); ++set_it)
	{
		std::cout<<*set_it<<" ";
	}
	
	std::cout<<std::endl;
	
	return 0;
}