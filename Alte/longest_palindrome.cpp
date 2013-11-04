#include <string>
#include <iostream>

/*
 * Problem: find longest palindrome in a string
 * Solution: 
 * - iterate on string
 * - from current index, go left & right as long as a[left] == a[right]
 * 
 * start from 2nd char:
 * 		while:
 * 			center = current_index/2
 * 			left = center - 1
 * 			right = center + 1
 * 			while is_palindrome
 * 				--left
 * 				++right
 * 
 * etc
 */

using namespace std;

string findLongestPalindrome( string str )
{
	string longestPalindrome = "";
	int    longestLength     = 1;
	for( int i=1; i<str.length()*2 - longestLength; i++ )
	{
		int center = i/2;             // index of the current "center" within "str"
		int left   = center - 1;   // used to iterate left  of the center
		int right  = center + 1;   // used to iterate right of the center
		if ( (i%2)==0 )                  // to account for palindromes with even number of letters.
			left = center;

		while( left>=0 && right < str.length()    // while left and right are in limits
			&& str[left] == str[right] )       //  and left and right are equal
		{
			int length = right - left + 1;
			if( length > longestLength )              // if this is our longest:
			{
				longestLength = length;                     //|-- update
				longestPalindrome = str.substr(left, length);   //|
			}
			left--;                  //|-- expand left and right out from center
			right++;                 //|
		}
	}
	return (longestPalindrome);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr<<"usage: ./lgstPal <str>\n";
		return 1;
	}
	std::string str(argv[1]);

	std::cout<<"palindrom: "<<findLongestPalindrome(str)<<std::endl;

	return 0;
}
