#include <iostream>
#include <string.h>
#include <stdio.h>

/**
 * Problem: print nth last element
 * Solution a: go with a lazy index
 * Solution b: recursion
 */


void
printNthLast(unsigned n, const char* p)
{
	const char* lazy = p;
	unsigned i = 0;
	for (; i < n && p && *p; ++i, ++p);
	if (i != n)
	{
		std::cout<<"string has only "<<i<<" chars!\n";
		return;
	}
	
	while (p && *p)
	{
		++p;
		++lazy;
	}
	
	std::cout<<n<<" last element: "<<lazy[0]<<"\n";
	return;
}

unsigned size = 0;

void
printRecLast(const char* p, unsigned n, unsigned count)
{
	if (p && *p)
	{
		printRecLast(p+1, n, count+1);
		if ((size >= n) && (count == size - n))
		{
			std::cout<<p[0]<<"\n";
		};
	}
	else
	{
		size = count;
		std::cout<<"str size: "<<size<<"\n";
	}
}

int main()
{
	char p[] = "The brown fox jumped over the lazy dog";
	printNthLast(38, p);
	
	printRecLast(p, 38, 0);
	
	return 0;
}
