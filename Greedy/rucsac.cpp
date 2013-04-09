#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<int> init_vect;
std::vector<int> solution;
int sum = 9;

void greedyRucsac()
{
	int crtCap = 0;
	int i = 0;
	
	while ((i < init_vect.size()) && (crtCap < sum))
	{
		if (crtCap + init_vect.at(i) <= sum)
		{
			solution.push_back(init_vect.at(i));
			crtCap = crtCap + init_vect.at(i);
		}
		i++;
	} //while
	
	
}


int main()
{

	init_vect.push_back(1);
	init_vect.push_back(2);
	init_vect.push_back(3);
	init_vect.push_back(4);
	init_vect.push_back(5);	

	std::sort(init_vect.begin(), init_vect.end());
	
	
	greedyRucsac();
	
	std::cout<<"solution:\n";
	
	std::copy(solution.begin(), solution.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout<<"\n";

	return 0;
}
