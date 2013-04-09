#include <iostream>
#include <vector>

int
biggestSum(std::vector<int> vect_int)
{
	if (vect_int.empty())
	{
		return 0;
	}

	int max_so_far = vect_int.at(0);
	int max_ending_here = vect_int.at(0);

	for(unsigned i = 1; i < vect_int.size(); ++i)
	{
		max_ending_here += vect_int.at(i);
		if (max_ending_here < 0)
		{
			max_ending_here = 0;
		}
		else if (max_so_far < max_ending_here)
		{
			max_so_far  = max_ending_here;
		}

		std::cout<<"max_so_far: "<<max_so_far<<"\n";
	}

	return max_so_far;
}

int main()
{
	std::vector<int> vect_int;
	vect_int.push_back(41);
	vect_int.push_back(-2);
	vect_int.push_back(5);
	vect_int.push_back(-50);
	vect_int.push_back(-3);
	vect_int.push_back(32);
	vect_int.push_back(1);
	vect_int.push_back(5);
	vect_int.push_back(-2);

	std::cout<<"sum: "<<biggestSum(vect_int)<<"\n";

	return 0;
}
