#include <string>
#include <vector>
#include <iostream>

using namespace std;

int longest_common_subsequence(std::string string1, std::string string2)
{
        unsigned int i, j;

        unsigned int n = string1.length();
        unsigned int m = string2.length();

        if(n == 0 || m == 0) {
                return -1;
        }

        vector< vector<int> > matrix(n + 2);

        for(i = 0; i <= n+1; i++) {
                matrix[i].resize(m + 2);
        }

        for(i = 0; i <= n+1; i++) {
                matrix[i][0] = i;
        }

        for(j = 0; j <= m+1; j++) {
                matrix[0][j] = j;
        }

        for(i = n+1; i >= 1; i--) {
                for(j = m+1; j >= 1; j--) {
	                std::cout << "n: " << n+1 << " m: " << m+1 << " i: " << i << " j: " << j << endl;
                        if(i == n+1 || j == m+1) {
                                matrix[i][j] = 0;
                        } else if(string1.at(i-1) == string2.at(j-1)) {
                                matrix[i][j] = 1 + matrix[i + 1][j + 1];
                        } else {
                                matrix[i][j] = max(matrix[i + 1][j], matrix[i][j + 1]);
                        }
                }
        }
/*
        for(i = 0; i <= n+1; i++) {     // print matrix
                wcout << endl;
                for(j = 0; j <= m+1; j++){
                        wcout << matrix[i][j] << " ";
                }
        }
        wcout << L" = ";
*/
        return matrix[1][1];
}


int main(int argc, char* argv[])
{
	if(argc!=3)
	{
		std::cout<<"longest str1 str2\n";
		return -1;
	}
	
	std::string str1, str2;
	std::cin >> str1;
	std::cin >> str2;
	
	std::cout<<str1<<"\n"<<str2<<"\n";
	
	
	int res = longest_common_subsequence(str1, str2);
	
	std::cout<<"res="<<res<<"\n";
	
}
