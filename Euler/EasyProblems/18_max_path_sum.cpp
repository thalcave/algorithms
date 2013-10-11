#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <stdexcept>
#include <fstream>
#include <string.h>
#include <errno.h>
#include <boost/algorithm/string.hpp>
#include <vector>

/**
 * 
 *
 * By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.

3
7 4
2 4 6
8 5 9 3

That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom of the triangle below:

Start from the bottom:
a[x-1, y] += max{a[x,y], a[x, y+1]}
*/


unsigned long
convertString(std::string const& str)
{
	//std::cout <<str<< " + ";
	try
	{
		unsigned long nr = boost::lexical_cast<unsigned long>(str);
		return nr;
        } catch(boost::bad_lexical_cast const& bc) {
                std::cout<<"caught error: "<<bc.what()<<" str: "<<str<<"\n";
		throw;
        }
	
}

std::vector<std::string>
getInputData(std::string const& input_file)
{
	std::ifstream input(input_file.c_str());
	if (!input.good())
	{
		throw std::runtime_error("Error opening file: " + input_file + "; reason: " + std::string(strerror(errno)));
	}
	
	char buffer[1024];
	unsigned line_no = 0;
	
	memset(buffer, '\0', 1024);
	
	std::vector<std::string> input_data;
	
	while (input.getline(buffer, 1024).good())
	{
		//read line by line
		std::string tmp(buffer);
		if (tmp.empty())
		{
			continue;
		}
		
		input_data.push_back(tmp);
		++line_no;
		memset(buffer, '\0', 1024);
	}
	
	input.close();
	
	return input_data;
}


std::vector<unsigned> 
splitLine(const std::string& line)
{
	std::vector<unsigned> result;

	std::vector<std::string> str_vector;
	boost::split(str_vector, line, boost::is_any_of(" "));
	
	for (unsigned i = 0; i < str_vector.size(); ++i)
	{
		result.push_back(convertString(str_vector.at(i)));
		//std::cout<<"Added elem: "<<grid(line_no, i)<<"\n";
	}
	
	if (result.empty())
	{
		throw std::runtime_error("Invalid line: "+line);
	}
	
	return result;
}

void
maxPathSum(std::string const& input_file)
{
	std::vector<std::string> input_data = getInputData(input_file);
	std::cout<<"vector size: "<<input_data.size()<<"\n";
	
	if (input_data.empty())
	{
		std::cerr<<"Invalid data\n";
		return;
	}
	
	//keep intermediate results here
	//allocate a size big enough to keep all numbers from max. line
	std::vector<unsigned> previous_vector;
	
	//take every element of vector, split it into numbers
	std::vector<std::string>::const_reverse_iterator vect_it(input_data.rbegin());
	
	for (; vect_it != input_data.rend(); ++vect_it)
	{
		std::cout<<"\n--------------------------------------\n";
		std::cout<<"current numbers: "<<*vect_it<<"\n";

		std::vector<unsigned> current_numbers(splitLine(*vect_it));
		
		if (previous_vector.empty())
		{
			previous_vector.assign(current_numbers.begin(), current_numbers.end());
			continue;
		}
		
		unsigned csize = current_numbers.size();
		for (unsigned i = 0; i < csize; ++i)
		{
			unsigned max_no = std::max(previous_vector.at(i), previous_vector.at(i+1));
			current_numbers.at(i) += max_no;
			//std::cout<<"max_no: "<<max_no<<"\n";
		}
		
		previous_vector.assign(current_numbers.begin(), current_numbers.end());
	
	}
	
	std::cout<<"maxPathSum: "<<previous_vector.at(0)<<"\n";
	
	return;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"Usage: ./max_path <input_file>\n";
		return -1;
	}
	
	std::string input_file(argv[1]);
	
	maxPathSum(input_file);
	
	return 0;
}
