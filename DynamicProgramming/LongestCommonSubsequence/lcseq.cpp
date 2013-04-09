#include <string>
#include <iostream>


int longestCommonSubsequence(std::string s1, std::string s2)
{
        //if either string is empty, the length must be 0
        if (s1.empty() || s2.empty())
                return 0;

	int num[100][100];
        char letter1;
        char letter2;

        //Actual algorithm
        for(int i = 0; i < s1.length(); i++)
        {
                for(int j = 0; j < s2.length(); j++)
                {
                        letter1 = s1[i];
                        letter2 = s2[j];

                        if(letter1 == letter2)
                        {
                                if((i == 0) || (j == 0))
                                        num[i][j] = 1;
                                else
                                        num[i][ j] = 1 + num[i-1][ j-1];
                        }
                        else
                        {
                                if ((i == 0) && (j == 0))
                                        num[i][ j] = 0;
                                else if ((i == 0) && !(j == 0))   //First ith element
                                        num[i][j] = std::max(0, num[i][j - 1]);
                                else if (!(i == 0) && (j == 0))   //First jth element
                                        num[i][j] = std::max(num[i - 1][j], 0);
                                else if (!(i == 0) && !(j == 0))
                                        num[i][j] = std::max(num[i - 1][j], num[i][j - 1]);
                        }
                }//end j
        }//end i

        return num[s1.length()-1][s2.length()-1];
} //end LongestCommonSubsequence

int main()
{
	std::string s1("ABBAD"), s2("DBBAD");
	
	std::cout<<longestCommonSubsequence(s1, s2)<<"\n";
	return 0;
}
