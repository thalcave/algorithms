#include <iostream>
#include <vector>

#include "../common/Random.hpp"
#include "../common/GenVector.hpp"

/*
 * Problem: function to return a big amount (one million --> one billion) of unique random numbers,
		having only getRandom() which returns 0 <= n <=1
Solution: implement Durstenfeld solution:
To shuffle an array a of n elements (indices 0..n-1):
  for i from n − 1 downto 1 do
       j ← random integer with 0 ≤ j ≤ i
       exchange a[j] and a[i]

 */

int main()
{
	
	IntVector vect_int(10);
	unsigned size = vect_int.size();
	
	for (unsigned i = 0; i < size; ++i)
	{
		vect_int.at(i) = i;
	}
	
	Random rand;
	
	//last element of vector
	unsigned max = size -1;
	while (max)
	{
		//get random in [0, max]
		unsigned crand = rand.getRandom(0, max);
		//swap vect[crand] with vect[max]
		std::swap(vect_int.at(crand), vect_int.at(max));
		--max;
	}
	
	printVector(vect_int);
	
	
	return 0;
}