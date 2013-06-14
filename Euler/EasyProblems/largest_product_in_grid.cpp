#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <stdexcept>
#include <fstream>
#include <string.h>
#include <errno.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
/**
 * In the 2020 grid below, four numbers along a diagonal line have been marked in red.

08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08
49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00
81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65
52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91
22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80
24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50
32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70
67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21
24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72
21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95
78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92
16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57
86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58
19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40
04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66
88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69
04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36
20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16
20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54
01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48

The product of these numbers is 26  63  78  14 = 1788696.

What is the greatest product of four adjacent numbers in the same direction (up, down, left, right, or diagonally) in the 2020 grid?



 */

using namespace boost::numeric::ublas;

void
parseLine(std::string const& line, matrix<unsigned>& grid, unsigned line_no)
{
	if (line_no >= 20)
	{
		std::cerr<<"line_no: "<<line_no<<"\n";
		throw std::runtime_error("Invalid file, too many lines; current line: " + line);
	}
	
	std::vector<std::string> str_vector;
	boost::split(str_vector, line, boost::is_any_of(" "));
	
	//std::cout<<"vector size"<<str_vector.size()<<"\n";
	
	if (str_vector.size() != 20)
	{
		std::cerr<<"csize: "<<str_vector.size()<<"\n";
		throw std::runtime_error("Invalid line: " + line);
	}
	
	for (unsigned i = 0; i < str_vector.size(); ++i)
	{
		grid(line_no, i) = boost::lexical_cast<unsigned>(str_vector.at(i));
		//std::cout<<"Added elem: "<<grid(line_no, i)<<"\n";
	}

}

unsigned long
getMaxProduct(matrix<unsigned> const& grid)
{
	unsigned long max_product = 0;
	//unsigned long adjacent_product = 0;
	
	unsigned a, b, c, d;
	
	std::cout<<"grid size1: "<<grid.size1()<<"\n";
	std::cout<<"grid size1: "<<grid.size2()<<"\n";
	
	for (unsigned i = 0; i < grid.size1(); ++i)
	{
		for (unsigned j = 0; j < grid.size2(); ++j)
		{
			if (i+3 < grid.size1())
			{
				if (j+3 <  grid.size2())
				{
					//diagonal 1
					//std::cout<<"j = "<<j <<"\n";
					unsigned long current_product = grid(i, j) * grid(i+1, j+1) * grid(i+2, j+2) * grid(i+3, j+3);
					if (current_product > max_product)
					{
						max_product = current_product;
						a = grid(i, j);
						b = grid(i+1, j+1);
						c = grid(i+2, j+2);
						d = grid(i+3, j+3);
					}
					
					//left-to-right
					unsigned long lr_product = grid(i, j) * grid(i, j+1) * grid(i, j+2) * grid(i, j+3);
					if (lr_product > max_product)
					{
						max_product = lr_product;
						a = grid(i, j);
						b = grid(i, j+1);
						c = grid(i, j+2);
						d = grid(i, j+3);
					}

				}

				//diagonal 2
				if (j>=3)
				{
					//std::cout<<"j = "<<j <<"\n";
					unsigned long current_product = grid(i, j) * grid(i+1, j-1) * grid(i+2, j-2) * grid(i+3, j-3);
					if (current_product > max_product)
					{
						max_product = current_product;
						a = grid(i, j);
						b = grid(i+1, j-1);
						c = grid(i+2, j-2);
						d = grid(i+3, j-3);
					}
				}

				//up-down
				unsigned long ud_product = grid(i, j) * grid(i+1, j) * grid(i+2, j) * grid(i+3, j);
				if (ud_product > max_product)
				{
					max_product = ud_product;
					a = grid(i, j);
					b = grid(i+1, j);
					c = grid(i+2, j);
					d = grid(i+3, j);
				}
			}
			else
			{			
				//left-to-right
				if (j+3 < grid.size2())
				{
					unsigned long lr_product = grid(i, j) * grid(i, j+1) * grid(i, j+2) * grid(i, j+3);
					if (lr_product > max_product)
					{
						max_product = lr_product;
						a = grid(i, j);
						b = grid(i, j+1);
						c = grid(i, j+2);
						d = grid(i, j+3);
					}
				}
			}
		}
	}
	
	std::cout<<"a: "<<a<<" b: "<<b<<" c: "<<c<<" d: "<<d<<"\n";
	
	
	return max_product;
}

unsigned long
largestProduct(std::string const& input_file)
{
	std::ifstream input(input_file.c_str());
	if (!input.good())
	{
		throw std::runtime_error("Error opening file: " + input_file + "; reason: " + std::string(strerror(errno)));
	}
	
	char buffer[4096];
	matrix<unsigned> grid(20, 20);
	unsigned line_no = 0;
	
	while (input.getline(buffer, 4096).good())
	{
		//read line by line
		parseLine(std::string(buffer), grid, line_no);	//could throw
		++line_no;
		
		//std::cout<<buffer<<"\n";
	}
	
	return getMaxProduct(grid);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"Usage: ./lrg_pgrid <input_file>\n";
		return -1;
	}
	
	std::string input_file(argv[1]);
	
	std::cout<<"Largest product in grid: "<<largestProduct(input_file)<<"\n";
	
	return 0;
}
