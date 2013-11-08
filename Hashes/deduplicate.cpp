#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <list>
#include <fstream>
#include <unordered_map>
#include <stdexcept>

/*
 * Problems: read lines from a file and remove duplicates; the order should be: duplicated line should be last
 * input: lines=[A,B,A] -> output: lines=[B,A]

 Solution
 1. 
 - add each line in a deque of strings
	after adding (at end), check in deque if a similar line exists and delete it
complexity: space: O(n), time O(n^2)
	
2. keep read lines in a deque and a hash with iterators to deque
if a line exists in deque, update the iterator
- 
 */

//keep strings in this list
typedef std::list<std::string> StringList;
//iterator to string list
typedef StringList::iterator ListIt;

//hash strings here for fast search
typedef std::unordered_map<std::string, ListIt> StringHash;

void
writeOutput(std::string const& out, StringList const& unique_strings)
{
	//open file
	std::ofstream output(out);
	if (!output.good())
	{
		throw std::runtime_error("Cannot open file: " + out);
	}
	
	StringList::const_iterator list_it(unique_strings.begin());
	for (; list_it != unique_strings.end(); ++list_it)
	{
		output << *list_it<<"\n";
	}
	
	output.close();
}

void
addString(StringList& result, std::string const& cline, StringHash& str_hash)
{
	//search cline in str_hash
	StringHash::iterator found_hash(str_hash.find(cline));
	if (found_hash == str_hash.end())	//string not found in hash --> no duplicate
	{
		//add string in list
		//constant
		result.push_back(cline);
		ListIt last_elem = result.end();
		--last_elem;
		str_hash.insert(std::make_pair(cline, last_elem));
	}
	else
	{
		//string found in hash --> already exists in list
		//remove it from list
		result.erase(found_hash->second);
		//add it at the end
		result.push_back(cline);
		//update iterator
		
		ListIt last_elem = result.end();
		--last_elem;
		found_hash->second = last_elem;
	}
}

StringList
readInputFile(std::string const& in)
{
	StringList result;
	StringHash str_hash;
	
	//open input file
	std::ifstream input(in);
	if (!input.good())
	{
		throw std::runtime_error("Cannot open file: " + in);
	}
	
	std::string current_line;
	//getline discards \n
	while (!std::getline(input, current_line).eof())
	{
		addString(result, current_line, str_hash);
	}
	
	input.close();
	
	return result;
}

void
processFile(std::string const& in, std::string const& out)
{
	//read input file
	//write output file
	writeOutput(out, readInputFile(in));
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr<<"Usage: ./deduplicate <input> <output>\n";
		return -1;
	}
	
	try
	{
		processFile(std::string(argv[1]), std::string(argv[2]));
	} catch (std::runtime_error const& rte) {
		std::cerr<<"Error encountered: "<<rte.what()<<"\n";
		return -1;
	} catch (std::exception const& rte) {
		std::cerr<<"Error encountered: "<<rte.what()<<"\n";
		return -2;
	} catch (...) {
		std::cerr<<"Unknown error encountered: \n";
		return -3;
	}

	
	return 0;
}
