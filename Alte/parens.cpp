#include <string>
#include <iostream>
#include <string.h>

/*
 * Problem: Print all valid combinations of n-pairs of parens

n: 3
S: ()()(), ((())), ()(()), (())()

Solution: recursive approach:
	no. of ( parens left
	no. of ) parens left
	string to hold result
*/

//left = how many ( parens are left
//right = how many ) parens are left

void
printCombo(int left, int right, char str[], unsigned count)
{
	if (left < 0 || right < left)	//invalid combination
		return;
	
	if (!left && !right)	//no parens left
	{
		std::cout<<str<<"\n";
		return;
	}
	
	if (left > 0)
	{
		str[count] = '(';
		printCombo(left-1, right, str, count + 1);
	}
	
	if (right > 0)
	{
		str[count] = ')';
		printCombo(left, right -1 , str, count + 1);
	}
}

int main()
{
	unsigned n = 4;
	char* str = new char[n*2 + 1];
	memset(str, '\0', n*2+1);
	
	printCombo(n, n, str, 0);
	
	return 0;
}
