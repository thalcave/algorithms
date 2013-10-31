#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

/*
 *Problem: sort an array of strings so that all anagrams are next to each other

Solution:
implement a comparator which sorts the strings and then compares them
*/

struct CompareStrings
{
	bool operator()(std::string const& s1, std::string const& s2)
	{
		std::string tmp1(s1);
		std::sort(tmp1.begin(), tmp1.end());
		
		std::string tmp2(s2);
		std::sort(tmp2.begin(), tmp2.end());

		return tmp1 < tmp2;
	}
};


int main()
{
	std::vector<std::string> v1;
	v1.push_back("ana");
	v1.push_back("aan");
	v1.push_back("nna");
	v1.push_back("nana");
	v1.push_back("nand");
	v1.push_back("fana");
	v1.push_back("dana");
	v1.push_back("anda");
	
	CompareStrings cmp;
	std::sort(v1.begin(), v1.end(), cmp);
	
	std::copy(v1.begin(), v1.end(), std::ostream_iterator<std::string>(std::cout, " "));
	std::cout<<std::endl;
	
	return 0;
}
