#include <iostream>
#include <string>
#include <stdexcept>

/*
 * Reverse in-place the order of words in a string
 * e.g this is a contrived input ---> input contrived a is this
 * 
 * 
 * Algo:
 * find the first word from the back
 * move it to beginning
 * move the rest of letters to back
 */

std::string::size_type
rfind(const std::string& str, char ch, std::string::size_type start, std::string::size_type end)
{
	if (str.size() < end || str.size() < start)
	{
		throw std::logic_error("invalid string size");
	}
	
	std::string::size_type idx(end);
	for (; idx > start && idx; --idx)
	{
		if (str.at(idx) == ch)
		{
			return idx;
		}
	}
	
	return std::string::npos;
}

void
moveStr(std::string& str, std::string::size_type start, std::string::size_type end, std::string const& cword)
{
	std::cout<<"["<<str<<"]"<<"\n";
	std::cout<<"start: "<<start<<" end: "<<end<<" cword: "<<cword<<"\n";
	
	const std::string::size_type step(cword.size()+1);	//1 is for the space
	std::string::size_type idx(end-step+1);
	while (idx > start)
	{
		std::cout<<"idx: "<<idx<<"\n";
		--idx;
		str.at(idx+step) = str.at(idx);
	}
	
	std::cout<<"["<<str<<"]"<<"\n";
	str.replace(start, cword.size(), cword);
	str.at(start + cword.size()) = ' ';
	
	std::cout<<"["<<str<<"]"<<"\n-------------------------------------------\n";

}

void
reverseWords(std::string& str)
{
	if (str.empty())
	{
		return;
	}
	
	//last char in string
	std::string::size_type end(str.size()-1);
	while (str.at(end) == ' ' && end)
	{
		--end;
	}
	
	if (!end)
	{
		std::cerr<<"no words found\n";
		return;
	}

	std::string::size_type start(0);
	
	//search from the end first ' ' char
	while (start < end)
	{
		std::string::size_type found = rfind(str, ' ', start, end);
		if (found != std::string::npos)
		{
			std::cout <<found<<"\n";
			//take [found+1, end] substr
			std::string cword = str.substr(found+1, end -found);
			std::cout<<"cword: ["<<cword<<"]\n";
			
			//move this cword at the beginning of string
			moveStr(str, start, end, cword);
			
			start += cword.size() + 1;	//because we added a ' '
		}
		else
		{
			break;
		}
	}
	
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"Usage: ./reverse <\"string\">\n";
		return -1;
	}
	
	std::string mystr(argv[1]);
	reverseWords(mystr);
	std::cout<<"reversed words: ["<<mystr<<"]\n";
	
	return 0;
}
