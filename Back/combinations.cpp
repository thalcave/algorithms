#include <iostream>
#include <vector>
#include <iterator>

void print(std::vector<int> vect)
{
	std::cout<<"Vector = ";
	copy(vect.begin(), vect.end(), std::ostream_iterator<int>(std::cout," "));
	std::cout<<"\n";
}

/*#include <iostream.h>
const int b=4;  // ------- b and d non negative
const int d=2;  // ------- b is not smaller than d
int A[d];  int id=0;

void printar(int A[], int size)
{for (int i=0; i<size; i++) {cout <<A[i]<<" ";} }

void generate()
{int ib=1;
do {// -------- For id==0 the first element is always ok.
    // -------- 'increasing' dispositions: see the > below.
    if ((id==0) || (ib > A[id-1]))
       {A[id]=ib; id=id+1;
       if (id==d) {printar(A,d); cout << "\n";} else generate();
       id=id-1;};
    ib=ib+1;}
while (ib<b+1);}*/




void generate(std::vector<int> vect, int n, int p)
{
	int k = 1;
	do
	{
		if( vect.empty() || ( !vect.empty() && k > vect.back() ))
		{
			vect.push_back(k);
			if( vect.size() == p )
				print(vect);
			else
				generate(vect, n, p);
			vect.pop_back();
		}
		++k;
	}
	while( k < n + 1);
}

/* generates n!/p!(n-p)! */
int main()
{
	std::vector<int> vect;
	int n = 6; 
	int p = 3;

	generate(vect, n, p);
}
