#include <iostream>

//create a hash from a string
unsigned long
hash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while ( (c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"usage: djb2 string\n";
		return -1;
	}

	std::string str(argv[1]);
	std::cout<<hash(str.c_str())<<"\n";

	std::cout<<"a"[3>>1]<<"\n";
	return 0;
}