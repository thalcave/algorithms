#include <iostream>

//create a hash from a string
unsigned long
hash(const char *str)
{
	unsigned long hash = 0;
        int c;

        while (c = *str++)
	{
            hash = c + (hash << 6) + (hash << 16) - hash;
	    std::cout<<"hash: "<<hash<<"\n";
	}

        return hash;
}


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"usage: ./sdmb string\n";
		return -1;
	}

	std::string str(argv[1]);
	std::cout<<hash(str.c_str())<<"\n";

	return 0;
}