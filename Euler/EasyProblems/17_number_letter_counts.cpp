#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <stdexcept>
#include <map>
#include <math.h>

/*
 * If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?


NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. 
The use of "and" when writing out numbers is in compliance with British usage.


Solution:
* build map of precomputed values: 1 --> 3 (one)
				   2 --> 3 (two)
					...
				   30 --> 6 (thirty)
					....
				1000 --> 11 (one thousand)

 */


typedef std::map<unsigned, unsigned> MapLetterCount;
MapLetterCount letter_count;

void
buildLetterCount()
{
	letter_count[1]=3;
	letter_count[2]=3;
	letter_count[3]=5;
	letter_count[4]=4;
	letter_count[5]=4;
	letter_count[6]=3;
	letter_count[7]=5;
	letter_count[8]=5;
	letter_count[9]=4;
	letter_count[10]=3;
	letter_count[11]=6;
	letter_count[12]=6;
	letter_count[13]=8;
	letter_count[14]=8;
	letter_count[15]=7;
	letter_count[16]=7;
	letter_count[17]=9;
	letter_count[18]=8;
	letter_count[19]=8;
	letter_count[20]=6;
	letter_count[30]=6;
	letter_count[40]=5;
	letter_count[50]=5;
	letter_count[60]=5;
	letter_count[70]=7;
	letter_count[80]=6;
	letter_count[90]=6;
	letter_count[100]=10;
	letter_count[200]=10;
	letter_count[300]=12;
	letter_count[400]=11;
	letter_count[500]=11;
	letter_count[600]=10;
	letter_count[700]=12;
	letter_count[800]=12;
	letter_count[900]=11;
	letter_count[1000]=11;

}

//return 0 if not found, the value otherwise
unsigned
getExisting(unsigned number)
{
	MapLetterCount::const_iterator found(letter_count.find(number));
	return  found != letter_count.end() ? found->second : 0;
}
unsigned getNoLetters(unsigned number)
{
	if (number > 1000)
	{
		throw std::logic_error("invalid number, bigger than 1000");
	}
	
	//search it first in precomputed
	unsigned no = getExisting(number);
	if (no)
	{
		return no;
	}
	
	ldiv_t result = ldiv(number, 100);
	
	if (result.quot)	//number is in form XYZ
	{
		no = getExisting(result.quot);	//should be there
		if (!no)
		{
			std::cerr<<"cannot find no. of letters for: "<<result.quot<<"\n";
			throw std::logic_error("cannot find no. of letters");
		}
		
		//now add len("hundredand") = 10
		no +=10;
	}
	
	//take the remainder, which is in form YZ
	unsigned tmp = getExisting(result.rem);
	if (tmp)
	{
		no += tmp;
		return no;
	}
	
	result = ldiv(result.rem, 10);
	
	tmp = getExisting(result.quot * 10);
	if (!tmp)
	{
		std::cerr<<"cannot find no. of letters for: "<<result.quot<<"\n";
		throw std::logic_error("cannot find no. of letters");
	}
	no += tmp;
	
	tmp = getExisting(result.rem);
	if (!tmp)
	{
		std::cerr<<"cannot find no. of letters for: "<<result.rem<<"\n";
		throw std::logic_error("cannot find no. of letters");
	}
	
	no += tmp;

	return no;
}

unsigned
numberLetterCounts()
{
	unsigned sum = 0;
	buildLetterCount();
	
	for (unsigned i = 1; i <= 1000; ++i)
	{
		unsigned no = getNoLetters(i);
		std::cout<<"count("<<i<<") = "<<no<<"\n";
		sum += getNoLetters(i);
	}

	return sum;
}


int main(int argc, char* argv[])
{
	std::cout<<"number letter count: "<<numberLetterCounts()<<"\n";
	
	return 0;
}
