#include <iostream>
#include <string>
#include <vector>
#include <map>


/**
 * most common occurence of a letter in a string
 * - parse string, count letters (65-90: A-Z; 97-122 a-z)
 * - find a way to keep the max.
 * 
 * modified: 10 most encountered letters
 */

typedef std::multimap<unsigned, unsigned> LetterOccurrence;
typedef LetterOccurrence::iterator LetterOccurrenceIt;
LetterOccurrence letters_occurrence;

/*
 * search for 'count' in multimap (key)
 * if found
 * 	if 'letter' matches (value)
 * 		increment key
 * 	else
 * 		insert(count, letter)
 * else
 * 	insert (count, letter)
 * 	
 */
void
addLetterOccurence(unsigned count, unsigned letter)
{
	std::pair<LetterOccurrenceIt, LetterOccurrenceIt> ret = letters_occurrence.equal_range(count);
	LetterOccurrenceIt res_it = ret.first;
	for (; res_it != ret.second; ++res_it)
	{
		if (res_it->second == letter)	//found the letter
		{
			//remove old (key,value)
			letters_occurrence.erase(res_it);
			letters_occurrence.insert(std::make_pair(++count, letter));
			
			std::cout<<"Updated letter: "<<letter<<" occurence: "<<count<<"\n";
			return;
		}
	}
	
	letters_occurrence.insert(std::make_pair(++count, letter));
	std::cout<<"Added letter: "<<letter<<" occurence: "<<count<<"\n";
	return;
}

void
mostTenOccurences()
{
	std::cout<<"Ten most occurrences:\n";
	LetterOccurrence::const_reverse_iterator crit = letters_occurrence.rbegin();
	unsigned count = 10;
	for (; crit != letters_occurrence.rend() && count; ++crit, --count)
	{
		std::cout<<static_cast<char>(crit->second)<<" --> "<<crit->first<<"\n";
	}
}

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
		
		//take prev_val, to search in multimap
		unsigned prev_val = occurence_vector.at(idx)++;
		
		if (occurence_vector.at(idx) > max_occurence)
		{
			max_occurence = occurence_vector.at(idx);
			most_char = ch;
		}
		
		addLetterOccurence(prev_val, ch);
	}
	
	std::cout<<"Most common occurence: "<<most_char<< " : "<<max_occurence<<"\n";
	mostTenOccurences();
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
