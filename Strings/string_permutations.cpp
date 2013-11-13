#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <iterator>

/*
 * Problem: print all permutations of a string
 * Solution: compute recursively
 * 
 * perm(0) -> {}
 * perm(1) --> {str[0]}
 * perm(2) --> str[1] + {str[0]}
 * 
 */

typedef std::vector<std::string> StringVector;

void
printVector(StringVector const& vint)
{
    std::copy(vint.begin(), vint.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout<<"\n";
}



StringVector
perm(std::string const& str, unsigned len)
{
	if (!len)
	{
		return StringVector();
	}
	
	if (len == 1)
	{
		return StringVector(1, str.substr(0, 1));
	}
	
	StringVector cvector = perm(str, len - 1);
	char ch = str[len - 1];	//take last character from string
	
	StringVector result;	//result of concatenation(cvector, ch)
	
	//printVector(cvector);

	StringVector::const_iterator wit(cvector.begin());
	for (; wit != cvector.end(); ++wit)
	{
		std::string const& word = *wit;
		for (unsigned i = 0 ; i <= word.size(); ++i)
		{
			//result.push_back(merge(word, i, ch));
			//merge w[0:i], ch, w[i:len(w)]
			std::string p1 = word.substr(0, i);
			p1 += ch;
			p1 += word.substr(i, word.size());
			result.push_back(p1);
			
			//std::cout<<"p1: "<<p1<<"\n";
		}
	}
	
	return result;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"Usage: ./perm <\"string\">\n";
		return -1;
	}
	
	std::string mystr(argv[1]);
	StringVector res = perm(mystr, mystr.size());
	//res.push_back(mystr);
	printVector(res);
	
	return 0;
}
