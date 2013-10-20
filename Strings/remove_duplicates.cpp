/*
Problem: remove duplicates from string, without using additional structures
Solution: keep a tail where current element must be moved i.e where a duplicate exists
		if tail == i --> no op
		if tail != i --> tail denotes a duplicate --> safe to move current char in tail
*/

#include <iostream>
#include <string>

void removeDuplicates(std::string& str) 
{

	if (str.size() < 2)
		return;

	unsigned tail = 1;

	for (unsigned i = 1; i < str.size(); ++i) 
	{
		unsigned j = 0;
		for (; j < tail; ++j) 
		{
			if (str.at(i) == str.at(j)) 
				break;
		}
		
		if (j == tail) 
		{
			if (i != tail)
			{
				str.at(tail) = str.at(i);
			}
			++tail;
		}
	}
	
	str = str.substr(0, tail);
}


int main()
{
	std::string test("abcabdxy");
	removeDuplicates(test);
	std::cout<<test<<"\n";
	return 0;
}