#include <iostream>
#include <vector>
#include <iterator>

void print(std::vector<int> vect)
{
	std::cout<<"Vector = ";
	copy(vect.begin(), vect.end(), std::ostream_iterator<int>(std::cout," "));
	std::cout<<"\n";
}

void generate(int limit, std::vector<int> vect)
{
	int i = 1;
	do
	{
		/* search element */
		std::vector<int>::const_iterator found_it = find( vect.begin(), vect.end(), i);
		if(found_it == vect.end())
		{
			vect.push_back(i);
			if( vect.size() == limit - 1)
				print(vect);
			else
				generate(limit, vect);
			
			vect.pop_back();	
		}
		++i;
	}
	while( i < limit );
}


/* generates limit! permutations */
int main()
{
	std::vector<int> vect;
	int limit = 4; 
	
	generate(limit, vect);
}
