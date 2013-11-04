#include <iostream>
#include <sstream>
#include <math.h>

long double
power(long double  n, long double  m)
{
	long double result = n;
	for (long double  i = 1; i < m; ++i)
	{
		result *=n;
	}
	return result;
}

long double
powerRec(long double  n, long double  m)
{
	if (!m)
	{
		std::cout<<"m: "<<m<<"\n";
		return 1;
	}

	if (m>0)
	{
		return n * powerRec(n, --m);
	}

	return n * powerRec(n, ++m);
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr<<"usage: ./pw n m (n pow m)\n";
		return 1;
	}

	std::stringstream ostr;
	
	ostr << argv[1];
	long double  n;
	ostr >> n;

	ostr.clear();
	ostr << argv[2];
	long double  m;
	ostr >> m;

	std::cout<<"n: "<<n<<" m: "<<m<<"\n";
	std::cout<<"pow: "<<pow(n,m)<<"\n";


	if (!m)
	{
		std::cout<<"1"<<"\n";
		return 0;
	}

	if (!n)
	{
		std::cout<<"0"<<"\n";
		return 0;
	}

	std::cout<<"pow: "<<n/powerRec(n,m)<<"\n";

	return 0;
}
