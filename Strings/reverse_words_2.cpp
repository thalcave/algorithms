#include <iostream>
#include <string>
#include <stdexcept>

/*
 * Reverse in-place the order of words in a string
 * e.g this is a contrived input ---> input contrived a is this
 * 
 * 
 * Algo:
 * #1 reverse string
 * #2 reverse letters in words
 */

void
reverseString(std::string& str, std::string::size_type start, std::string::size_type end)
{
	if (str.empty())
	{
		return;
	}
	
	while (start < end)
	{
		char tmp = str.at(start);
		str.at(start) = str.at(end);
		str.at(end) = tmp;
		
		++start; --end;
	}
}
void
reverseLetters(std::string& str)
{
	if (str.empty())
	{
		return;
	}

	std::string::size_type cindex = 0;

	
	while (str.at(cindex) == ' ' && cindex < str.size())
	{
		++cindex;
	}
	std::string::size_type cpos = cindex;
	while (cindex < str.size())
	{
		if (str.at(cindex) == ' ')
		{
			//found word
			reverseString(str, cpos, cindex-1);
			++cindex;
			cpos = cindex;
		}
		else
		{
			++cindex;
		}
	}
	
	reverseString(str, cpos, cindex-1);
}
void
reverseWords(std::string& str)
{
	if (str.empty())
	{
		return;
	}
	
	//reverse string
	reverseString(str, 0, str.size()-1);
	std::cout<<"str: ["<<str<<"]\n";
	
	reverseLetters(str);
	std::cout<<"str: ["<<str<<"]\n";
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"Usage: ./rev2 <\"string\">\n";
		return -1;
	}
	
	std::string mystr(argv[1]);
	reverseWords(mystr);
	std::cout<<"reversed words: ["<<mystr<<"]\n";
	
	return 0;
}
