#include <iostream>
#include <string>
#include <vector>


/**
 * most common occurence of a letter in a string
 * - parse string, count letters (65-90: A-Z; 97-122 a-z)
 * - find a way to keep the max.
 */

void
mostCommonOccurence(std::string const& str)
{
	if (str.empty())
	{
		std::cerr<<"Empty string\n";
		return;
	}
	
	//construct a vector with 50 elems, 0 initial value
	std::vector<unsigned> occurence_vector(50, 0);
	
	unsigned max_occurence = 0;
	char most_char;
	
	std::string::const_iterator ch_it(str.begin());
	for (; ch_it != str.end(); ++ch_it)
	{
		//see if it's a letter
		const char& ch = *ch_it;
		
		std::cout<<"ch: "<<ch<<"\n";
		
		if (ch < 65)
		{
			continue;	//not a letter
		}
		
		std::vector<unsigned>::size_type idx = 0;
		
		if (ch <= 90)	//upper case letter
		{
			idx = ch - 65;
		}
		else if (ch >= 97 && ch <= 122)
		{
			idx = ch - 72;	//lower case letter
			
		}
		else
		{
			continue;	//not a letter
		}
		
		++occurence_vector.at(idx);
		if (occurence_vector.at(idx) > max_occurence)
		{
			max_occurence = occurence_vector.at(idx);
			most_char = ch;
		}
	}
	
	std::cout<<"Most common occurence: "<<most_char<< " : "<<max_occurence<<"\n";
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"Usage: ./most <string>\n";
		return -1;
	}
	
	std::string mystr(argv[1]);
	mostCommonOccurence(mystr);
	
	return 0;
}
