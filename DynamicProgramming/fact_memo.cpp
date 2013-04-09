//fmicu: memoization=optimization technique by having function calls avoid repeating the calculation of results for previously-processed input

#include <iostream>
#include <map>

unsigned long factorial_func(unsigned long n)
{
	if(!n) 
	{
		return 1;
	}	

	return factorial_func(n-1)*n;
}

typedef std::map<unsigned long, unsigned long> ValueMap;

ValueMap computed_values;

unsigned long memo_func(unsigned long n)
{
	unsigned long x;

	ValueMap::const_iterator found = computed_values.find(n);
	if(found != computed_values.end())
		return found->second;

	if(!n) return 1;

	x = factorial_func(n-1) *n;

	computed_values[n] = x;
	return x;
}

/*  bottom-up approach (calculate the smaller values of func first, then build larger values from them) */
unsigned long func_bottom_up(unsigned long n)
{
	unsigned long prev_func = 2;
	unsigned long curr_func = 1;
	for(; n > 1; n--)
	{
		unsigned long new_func = prev_func * curr_func;
		++prev_func;
		curr_func = new_func;
	}

	return curr_func;
}



int main()
{
	unsigned long n = 10;

	{
		clock_t ticks = clock();
		unsigned long fact = factorial_func(n);
		std::cout<<"Fact="<<fact<<"\n";
		std::cout << "recursive factorial: "<< clock() - ticks << std::endl;
	}

	{
		clock_t ticks = clock();
		unsigned long fact = func_bottom_up(n);
		std::cout<<"Fact="<<fact<<"\n";
		std::cout << "func_bottom_up: "<< clock() - ticks << std::endl;
	}
	{
		clock_t ticks = clock();
		unsigned long fact = memo_func(n);
		std::cout<<"Fact="<<fact<<"\n";
		std::cout << "memo_func: "<< clock() - ticks << std::endl;
	}


	return 0;
}
