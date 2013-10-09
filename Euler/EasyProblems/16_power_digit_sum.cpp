#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <map>
#include <algorithm>

/*
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?


#1 compute 2^1000
	2^1000 = 2^99 + 2^99
	f(n) = f(n-1) + f(n-1)
#2 add digits
*/

//map 2^power --> result (string form)
typedef std::map<unsigned, std::string> MapPower;
MapPower powers_two;

typedef std::string::size_type StrIndex;
typedef std::string::const_reverse_iterator StrIt;

//add 2 big numbers (given in string)
std::string
addBigNumbers(const std::string& n1, const std::string& n2)
{
	if (n1.empty())
	{
		return n2;
	}
	if (n2.empty())
	{
		return n1;
	}
	
	StrIt s1 = n1.rbegin();
	StrIt s2 = n2.rbegin();
	
	//resulting sum
	std::string result;
	
	unsigned remainder = 0;
	
	//add digit by digit, starting with end
	while (s1 != n1.rend() && s2 != n2.rend())
	{
		//std::cout<<"s1: "<<*s1<<"\n";
		//std::cout<<"s2: "<<*s2<<"\n";

		unsigned res = remainder + boost::lexical_cast<unsigned>(*s1) + boost::lexical_cast<unsigned>(*s2);
		result += boost::lexical_cast<std::string>(res%10);
		
		if (res > 9)
		{
			remainder = res/10;
		}
		else
		{
			remainder = 0;
		}
		
		++s1; ++s2;
	}
	
	if (s1 != n1.rend())
	{
		std::string leftover = std::string(s1, n1.rend());
		unsigned res = boost::lexical_cast<unsigned>(leftover);
		if (remainder)
		{
			res += remainder;
		}
		result += boost::lexical_cast<std::string>(res);
	} else if (s2 != n2.rend())
	{
		std::string leftover = std::string(s2, n2.rend());
		unsigned res = boost::lexical_cast<unsigned>(leftover);
		if (remainder)
		{
			res += remainder;
		}
		result += boost::lexical_cast<std::string>(res);
	} else 
	{
		if (remainder)
		{
			result += boost::lexical_cast<std::string>(remainder);
		}
	}

	
	
	std::reverse(result.begin(), result.end());
	//std::cout<<n1<<" + "<<n2 <<" = " << result<<"\n";
	
	return result;
}

void
buildMap()
{
	//pre-computed values
	powers_two[0]="1";
	powers_two[1]="2";
	powers_two[2]="4";
	powers_two[3]="8";
	powers_two[4]="16";
	powers_two[5]="32";
	powers_two[6]="64";
	powers_two[7]="128";
	powers_two[8]="256";
	powers_two[9]="512";
	powers_two[10]="1024";
	powers_two[11]="2048";
	powers_two[12]="4096";
	powers_two[13]="8192";
	powers_two[14]="16384";
	powers_two[15]="32768";
	powers_two[16]="65536";
}

std::string
powerOf2(unsigned number)
{
	//std::cout<<"powerOf2: "<<number<<"\n";
	//search in already computed values
	MapPower::const_iterator found(powers_two.find(number));
	if (found == powers_two.end())
	{
		powers_two[number] = addBigNumbers(powerOf2(number - 1),powerOf2(number - 1));
	}
	else
	{
		//std::cout<<"powerOf2: found "<<found->second<<"\n";
	}
	
	return powers_two[number];
}

unsigned
computeSum(std::string const& number)
{
	unsigned result = 0;
	for (StrIndex idx = 0; idx < number.size(); ++idx)
	{
		result += boost::lexical_cast<unsigned>(number.at(idx));
	}
	
	return result;
}

unsigned
power_digit_sum(unsigned number)
{
	buildMap();
	std::string result = powerOf2(number);
	
//	std::cout<<"2^"<<number<<" = " <<result<<"\n";
	
	return computeSum(result);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"Usage: ./pdg <power>\n";
		return -1;
	}
	
	unsigned number = boost::lexical_cast<unsigned>(std::string(argv[1]));
	std::cout<<"Power digit sum: "<<power_digit_sum(number)<<"\n";
	
	return 0;
}
