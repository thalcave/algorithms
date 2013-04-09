#include <iostream>

void
printArray(int* a, unsigned n)
{
	/*for (unsigned i = 0; i < n; ++i)
	{
		std::cout<<*(a+i)<<"\n";
	}*/

	while (n)
	{
		std::cout<<*a<< " ";
		++a;
		--n;
	}

	std::cout<<"\n";
}

void
printArrayRec(int* a, unsigned n)
{
	if (n)
	{
		std::cout<<*a<<" ";
		printArrayRec(a+1, n-1);
	}

}

void
printReverseArray(int* a, unsigned n)
{
	for (; n > 0; n--)
	{
		std::cout<<*(a+n-1)<<" ";
	}
}

void
printReverseArrayRec(int* a, unsigned n)
{
	if (n)
	{
		printReverseArrayRec(a+1, n-1);
		std::cout<<*a<<" ";
	}
}

int*
reverseArray(int* a, unsigned n)
{
	if (!n)
	{
		return 0;
	}

	int* rev = new int[n];

	unsigned i = 0;
	for (; n > 0; --n, ++i)
	{
		rev[i] = *(a+n-1);
	}

	return rev;
}

int main()
{
	unsigned n = 5;
	int a[] = {1, 2, 3, 4, 5};

	printArray(a, 5);
	
	printArrayRec(a, 5);
	std::cout<<"\n";

	printReverseArray(a, 5);
	std::cout<<"\n";

	printReverseArrayRec(a, 5);
	std::cout<<"\n";


	int* reversed_a = reverseArray(a, 5);
	std::cout<<"reversed:\n";
	printArray(reversed_a, 5);
	printReverseArray(reversed_a, 5);
	
	return 0;
}