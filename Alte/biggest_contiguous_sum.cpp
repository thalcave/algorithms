#include <iostream>
#include <vector>

int
biggestSum(std::vector<int> vect_int)
{
	if (vect_int.empty())
	{
		return 0;
	}

	int max_found = vect_int.at(0);
	int current_sum = vect_int.at(0);

	for(unsigned i = 1; i < vect_int.size(); ++i)
	{
		current_sum += vect_int.at(i);
		if (current_sum < 0)
		{
			current_sum = 0;	//start again
		}
		else if (max_found < current_sum)
		{
			max_found  = current_sum;
		}

		std::cout<<"max_found: "<<max_found<<"\n";
	}

	return max_found;
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
