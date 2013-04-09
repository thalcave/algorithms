//fmicu: memoization=optimization technique by having function calls avoid repeating the calculation of results for previously-processed input

#include <iostream>
#include <map>

unsigned int fib_func(int n)
{
	if(n == 0 )
		return 0;
	if(n == 1)
		return 1;
		
	return fib_func(n-1) + fib_func(n-2);
}

typedef std::map<int, unsigned int> ValueMap;
ValueMap computed_values;
ValueMap::const_iterator found;

/* fmicu: memoization, top-down approach (first break the problem into subproblems and then calculate and store values) */
unsigned int fib_memo(int n)
{
	found = computed_values.find(n);
	if(found == computed_values.end())
		computed_values[n]= fib_memo(n-1) + fib_memo(n-2);
	
	return computed_values[n];
}

/*  bottom-up approach (calculate the smaller values of fib first, then build larger values from them) */
unsigned int fib_bottom_up(int n)
{
	unsigned int prev_fib = 0;
	unsigned int curr_fib = 1;
	for(; n > 1; n--)
	{
		unsigned int new_fib = prev_fib + curr_fib;
		prev_fib = curr_fib;
		curr_fib = new_fib;
	}
	
	return curr_fib;
}
       
int main()
{
	int n = 45;

	{
		clock_t ticks = clock();
		computed_values[0] = 0;
		computed_values[1] = 1;	
		
		unsigned int fibo = fib_memo(n);
		std::cout<<"memo fibo="<<fibo<<"\n";
		std::cout << "fib_memo: "<< clock() - ticks << std::endl;
	}
		
	{
		clock_t ticks = clock();
		unsigned int fibo = fib_bottom_up(n);
		std::cout<<"bottom-up fibo="<<fibo<<"\n";
		std::cout << "fib_bottom_up: "<< clock() - ticks << std::endl;
	}
	
	{
		clock_t ticks = clock();
		unsigned int fibo = fib_func(n);
		std::cout<<"classic fibo="<<fibo<<"\n";
		std::cout << "fibo_func: "<< clock() - ticks << std::endl;
	}
	

	
	return 0;
}
