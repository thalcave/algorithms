#include <string>
#include <iostream>

void
printStr(char* p_str)
{
	/*if (p_str)
	{
		std::cout<<p_str;
		++p_str;
		printStr(p_str);
	}*/

	if (p_str && *p_str != '\0')
	{
		std::cout<<*p_str;
		++p_str;
		printStr(p_str);
	}
}

void
printReverseStr(char* p_str)
{
	/*if (p_str)
	{
		std::cout<<p_str;
		++p_str;
		printStr(p_str);
	}*/

	if (p_str && *p_str != '\0')
	{
		//p_str;
		printReverseStr(p_str+1);
		std::cout<<*p_str;
	}
	

}

void ret_str(char* s)
{
    if(*s != '\0')
         ret_str(s+1);

    std::cout<<*(s);
}

int main()
{
	//printStr("dsaseirupjmpcfjdsmf[]");
	//std::cout<<"\nreverse:\n";
	ret_str("florin");
	std::cout<<std::endl;
	printReverseStr("florin");
	std::cout<<"\n";

	return 0;
}