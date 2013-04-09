#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<unsigned long> init_vector;
std::vector<unsigned long> first_half;
std::vector<unsigned long> first_sums;

std::vector<unsigned long> second_half;
std::vector<unsigned long> second_sums;
std::vector<unsigned long>  solution;
unsigned long target = 484;

void
splitInitVector()
{
	unsigned long middle= init_vector.size() / 2;
	
	first_half.assign(init_vector.begin(), init_vector.begin() + middle);
	second_half.assign(init_vector.begin()+middle, init_vector.end());
	 
	
	
}

std::vector<int> comb_vector;

void print_comb(const std::vector<unsigned long>& values, const std::vector<int>& vect, std::vector<unsigned long>& sums)
{
	std::cout<<"Vector = ";
	copy(vect.begin(), vect.end(), std::ostream_iterator<int>(std::cout," "));
	std::cout<<"\n";

	std::vector<int> vect2;
	//int limit = 4;

	//permutations( 4, vect2);
	
	/* compute sum for this */
	unsigned long sum = 0;
	for (unsigned int i = 0; i < vect.size(); ++i)
	{
		sum += values.at(vect.at(i)-1);
	}
	
	sums.push_back(sum);
	
	//std::cout<<"SUM ="<<sum<<"\n";
	
	
}


void combinations(const std::vector<unsigned long>& values, int p, std::vector<unsigned long>& sums)
{
	int k = 1;
	do
	{
		if (comb_vector.empty() || ( !comb_vector.empty() && k > comb_vector.back() ))
		{
			comb_vector.push_back(k);
			if( comb_vector.size() == p )
				print_comb(values, comb_vector, sums);
			else
				combinations(values, p, sums);
			comb_vector.pop_back();
		}
		++k;
	}
	while( k < values.size() + 1);
}


void
computeSums(const std::vector<unsigned long>& values, std::vector<unsigned long>& sums)
{
	for (unsigned int p = 1; p <= values.size(); ++p)
	{
		comb_vector.clear();
		combinations(values, p, sums);
		
		
		
		
	}
}

void
computeSolution()
{
	std::vector<unsigned long>::const_reverse_iterator first_it(first_sums.rbegin());
	std::vector<unsigned long>::const_iterator second_it(second_sums.begin());
	
	do
	{
		if (*first_it == target)
		{
			std::cout<<"FOUND first_it = "<<*first_it<<"\n";
			return;
		}

		if (*second_it == target)
		{
			std::cout<<"FOUND second_it = "<<*second_it<<"\n";
			return;
		}
	

		unsigned long current_sum = *first_it + *second_it;
		
		std::cout<<"current_sum="<<current_sum<<"\n";
		
		if (current_sum > target)
		{
			++first_it;
		} else if (current_sum < target) {
			++second_it;
		} else 	{
			std::cout<<"FOUND SOLUTION ="<<target<<"\n";
			std::cout<<"first_it ="<<*first_it<<"\n";
			std::cout<<"second_it ="<<*second_it<<"\n";
			return;
		}
	}	
	while (first_it != first_sums.rend() && second_it != second_sums.end());
	
	std::cout<<"NO solution found :(!\n";
}

void
printVector(std::string const& vname, const std::vector<unsigned long>& values)
{
	std::cout<<vname<<"\n";
	std::copy(values.begin(), values.end(), std::ostream_iterator<unsigned long>(std::cout, " "));
	std::cout<<"\n-----------------------\n";
}

int main()
{
	init_vector.push_back(10);
	init_vector.push_back(231);
	init_vector.push_back(13);
	init_vector.push_back(14);
	init_vector.push_back(57);
	init_vector.push_back(127);
	init_vector.push_back(32);
	
	std::sort(init_vector.begin(), init_vector.end());
	
	splitInitVector();

	printVector("first half", first_half);
	printVector("second_half", second_half);



	computeSums(first_half, first_sums);
	std::sort(first_sums.begin(), first_sums.end());
	printVector("first_sums", first_sums);
	std::cout<<"#################################\n";
	computeSums(second_half, second_sums);
	std::sort(second_sums.begin(), second_sums.end());
	printVector("second_sums", second_sums);
	std::cout<<"#################################\n";


	computeSolution();
	
	
	printVector("solution", solution);

	return 0;
}
