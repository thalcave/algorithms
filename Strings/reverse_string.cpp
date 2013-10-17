#include <iostream>
#include <string.h>
#include <stdio.h>

void
printReverse(char* p)
{
	if (*p)
	{
		printReverse(p+1);
		std::cout<<*p;
	}
}

char*
reverse(char* p)
{
	if (!*p)
	{
		return 0;
	}
	
	size_t psize = strlen(p);	//O(n)
	
	char* reversed = new char[psize+1];
	memset(reversed, '\0', strlen(reversed));
	
	for (size_t idx = 0; idx < psize; ++idx)
	{
		reversed[idx] = p[psize-idx-1];	//O(n)
	}
	
	return reversed;
}

char result[100];

void
reverse_rec(char* p, int i)
{
	if (p && *p)
	{
		reverse_rec(p+1, i-1);
		//std::cout<<"i="<<i<<" p:"<<*p<<"\n";
		result[i] = *p;
	}
}

void
reverseInPlace()
{
	char str[] = "0123456789";
	
	char* start = str;
	char* end = str;
	
	while (*end)
	{
		++end;
	}
	
	--end;	//go to last char
	
	while (start < end)
	{
		//swap start and end
		char tmp = *start;
		*start = *end;
		*end = tmp;
		
		++start; --end;
	}
	
	std::cout<<"reversed: ["<<str<<"]\n";
}

int main()
{
	char p[] = "The brown fox jumped over the lazy dog";
	
	//char* p = new char[30];
	
	std::cout<<std::endl;
	
	printReverse(p);
	std::cout<<std::endl;
	
	std::cout<<reverse(p)<<std::endl;
	
	reverseInPlace();
	
	{
		char* rev = new char[strlen(p)+1];
		memset(rev, '\0', strlen(rev));
		//rev += strlen(rev)-1;
		
		int i = strlen(p)-1;
		//int i = 0;
		std::cout<<"strlen(p)"<<strlen(p)<<"\n";
		reverse_rec(p, i);
		
		std::cout<<"result:["<<result<<"]\n";
		std::cout<<"p:["<<p<<"]\n";
	}
	
	
	return 0;
}