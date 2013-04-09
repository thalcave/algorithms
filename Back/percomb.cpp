#include <iostream>
#include <vector>
#include <iterator>
#include <string>


std::vector<std::string> string_vector;

std::vector<int> comb_vector;

void print(std::vector<int> vect)
{
	std::cout<<"Vector2 = ";
	for(int i = 0; i < vect.size(); ++i)
		std::cout<<string_vector[comb_vector[vect[i]-1]-1]<<" ";
	//copy(vect.begin(), vect.end(), std::ostream_iterator<int>(std::cout," "));	
	std::cout<<"\n";
}


void permutations(int limit, std::vector<int> vect)
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
				permutations(limit, vect);
			
			vect.pop_back();	
		}
		++i;
	}
	while( i < limit );
}


void print_comb(std::vector<int> vect)
{
	std::cout<<"Vector = ";
	copy(vect.begin(), vect.end(), std::ostream_iterator<int>(std::cout," "));
	std::cout<<"\n";

	std::vector<int> vect2;
	int limit = 4;

	permutations( 4, vect2);
}


void combinations(int n, int p)
{
	int k = 1;
	do
	{
		if( comb_vector.empty() || ( !comb_vector.empty() && k > comb_vector.back() ))
		{
			comb_vector.push_back(k);
			if( comb_vector.size() == p )
				print_comb(comb_vector);
			else
				combinations(n, p);
			comb_vector.pop_back();
		}
		++k;
	}
	while( k < n + 1);
}


int main()
{
	string_vector.push_back("S1");
	string_vector.push_back("S2");
	string_vector.push_back("S3");
	string_vector.push_back("S4");
	string_vector.push_back("S5");
	string_vector.push_back("S6");		
	
	
	int n = 6; 
	int p = 3;

	combinations(n, p);
				
}
