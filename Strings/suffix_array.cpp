/*
 * Problem: Given a string S and an array of strings, T, design a method to search in S each string from T
 * 
 * Solution: use suffix array
 * Suffix array: contains all suffixes of a string and their start position, sorted in lexicographical order
 * e.g for 'abracadabra':
	a --> 10
	abra --> 7
	abracadabra --> 0
	acadabra --> 3
	adabra --> 5
	bra --> 8
	bracadabra --> 1
	cadabra --> 4
	dabra --> 6
	ra --> 9
	racadabra --> 2

 * 
 */


#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>

//pair containing the suffix string and its index: starting position from big string
typedef std::pair<std::string, unsigned> SuffixIndex;
typedef std::vector<SuffixIndex> SuffixArray;

void
searchStr(SuffixArray const& suf_array, int left, int right, std::string const& str)
{
	//do binary search on suffix_array
	if (left > right)
	{
		std::cout<<"String : "<<str<<" not found!\n";
		return;
	}
	
	unsigned middle = (right + left)/2;
	
	std::string cstr = suf_array.at(middle).first;
	//compare returns 0 if strings compare equal
	if (!cstr.compare(0, str.size(), str))
	
	{
		std::cout<<"Found str: "<<str<<" at: "<<suf_array.at(middle).second<<"\n";
		return;
	}
	
	if (suf_array.at(middle).first < str)
	{
		searchStr(suf_array, middle + 1, right, str);
	}
	else
	{
		searchStr(suf_array, left, middle -1, str);
	}
}

struct SuffixIndexComp
{
	bool operator()(SuffixIndex const& s1, SuffixIndex const& s2)
	{
		return s1.first < s2.first;
	}
};

void
search(std::string const& str, std::vector<std::string> const& vect_str)
{
	//create suffix array
	SuffixArray suf_array;
	
	for (unsigned i = 0; i < str.size(); ++i)
	{
		suf_array.push_back(std::make_pair(str.substr(i, str.size()), i));
		std::cout<<"pushed back: "<<str.substr(i, str.size())<<"\n";
	}
	
	//sort this vector
	std::sort(suf_array.begin(), suf_array.end(), SuffixIndexComp());
	
	for (unsigned i = 0; i < suf_array.size(); ++i)
	{
		std::cout<<suf_array.at(i).first<<" --> "<<suf_array.at(i).second<<"\n";
	}
	
	//for each element in str_vector, search it in suffix_array
	for (unsigned i = 0; i < vect_str.size(); ++i)
	{
		searchStr(suf_array, 0, suf_array.size(), vect_str.at(i));
	}
	
}

int main()
{
	std::string str("abracadabra");
	std::vector<std::string> vect_str;
	vect_str.push_back("ra");
	vect_str.push_back("abra");
	vect_str.push_back("cada");
	vect_str.push_back("abracadx");
	
	search(str, vect_str);
	
	return 0;
}

