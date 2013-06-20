#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <stdexcept>
#include <fstream>
#include <string.h>
#include <errno.h>
#include <boost/algorithm/string.hpp>
#include <vector>

/**
 * 
 *
 * Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.

37107287533902102798797998220837590246510135740250
46376937677490009712648124896970078050417018260538
74324986199524741059474233309513058123726617309629
91942213363574161572522430563301811072406154908250
23067588207539346171171980310421047513778063246676
89261670696623633820136378418383684178734361726757
28112879812849979408065481931592621691275889832738
44274228917432520321923589422876796487670272189318
47451445736001306439091167216856844588711603153276
70386486105843025439939619828917593665686757934951
62176457141856560629502157223196586755079324193331
64906352462741904929101432445813822663347944758178
92575867718337217661963751590579239728245598838407
58203565325359399008402633568948830189458628227828
80181199384826282014278194139940567587151170094390

etc


 */

/*one way is to separate lines in 10-digit numbers, add them separately and work with result
 * 
 * 
	3710728753|390210279|879799822|0837590246|510135740250
	4637693767|749000971|264812489|6970078050|417018260538

 */

/* struct holding X numbers of 50 digits each*/
struct LargeNumbersSum
{
	unsigned long sum_0, sum_1, sum_2, sum_3, sum_4;
	
	LargeNumbersSum(): sum_0(0), sum_1(0), sum_2(0), sum_3(0), sum_4(0) {}
	void addNumbers(std::string const& line);
	
	//compute whole sum
	void computeSum();
	unsigned getSurplus(unsigned long s0);
};

unsigned long
convertString(std::string const& str)
{
	//std::cout <<str<< " + ";
	try
	{
		unsigned long nr = boost::lexical_cast<unsigned long>(str);
        } catch(boost::bad_lexical_cast const& bc) {
                std::cout<<"caught error: "<<bc.what()<<" str: "<<str<<"\n";
		throw;
        }
	
}

void
LargeNumbersSum::addNumbers(std::string const& line)
{
	//line must be 50-chars long
	if (line.size() != 50)
	{
		throw std::runtime_error("Invalid line (there are no 50 digits here): "+line);
	}

	//std::cout<<"Add line:\n";
		
	//split the line in 5 tokens (each having 10 chars) and add them
	sum_0 += convertString(line.substr(0,10));
	sum_1 += convertString(line.substr(10,10));
	sum_2 += convertString(line.substr(20,10));
	sum_3 += convertString(line.substr(30,10));
	sum_4 += convertString(line.substr(40,10));
	
	//std::cout<<"\n---------------------------------\n";
}

unsigned 
LargeNumbersSum::getSurplus(unsigned long sum)
{
	/*if sum has N digits:
		if N > 10 --> return first N-10 digits
		else return 0
	*/
	std::string converted = boost::lexical_cast<std::string>(sum);
	if (converted.size() <= 10)
	{
		return 0;
	}
	
	return boost::lexical_cast<unsigned>(converted.substr(0, converted.size()-10));
}

void
LargeNumbersSum::computeSum()
{
	unsigned surplus = getSurplus(sum_4);
	std::cout<<"surplus for "<< sum_4<< " : "<<surplus<<"\n";
	
	sum_3 += surplus;
	surplus = getSurplus(sum_3);
	std::cout<<"surplus for "<< sum_3<< " : "<<surplus<<"\n";
	
	sum_2 += surplus;
	surplus = getSurplus(sum_2);
	std::cout<<"surplus for "<< sum_2<< " : "<<surplus<<"\n";

	sum_1 += surplus;
	surplus = getSurplus(sum_1);
	std::cout<<"surplus for "<< sum_1<< " : "<<surplus<<"\n";
	
	sum_0 += surplus;
	std::cout<<"final sum "<< sum_0<<"\n";
	
	
	std::string converted = boost::lexical_cast<std::string>(sum_0);
	std::cout<<"First 10 digits: "<<boost::lexical_cast<unsigned long>(converted.substr(0, 10))<<"\n";
}

void
largeSum(std::string const& input_file)
{
	std::ifstream input(input_file.c_str());
	if (!input.good())
	{
		throw std::runtime_error("Error opening file: " + input_file + "; reason: " + std::string(strerror(errno)));
	}
	
	char buffer[51];
	unsigned line_no = 0;
	
	LargeNumbersSum lr_sum;
	
	while (input.getline(buffer, 51).good())
	{
		//read line by line
		lr_sum.addNumbers(buffer);
		++line_no;
	}
	
	/*if (line_no != 100)
	{
		throw std::runtime_error("Invalid no. of lines, should be 100");
	}*/
	
	lr_sum.computeSum();
	
	
	return;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"Usage: ./lsum <input_file>\n";
		return -1;
	}
	
	std::string input_file(argv[1]);
	
	largeSum(input_file);
	
	return 0;
}
