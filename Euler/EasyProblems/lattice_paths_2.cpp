#include <stdio.h>
#include <stdlib.h>
#define SIZE 21

int main()
{
    long long totalways[SIZE][SIZE];
    int i, j;
    for(i=0; i<SIZE;i++){
       for(j=0;j<SIZE;j++){
           if(i==0 ||  j==0)
              totalways[i][j] = 1;
            else{
               totalways[i][j] = (totalways[i-1][j] + totalways[i][j-1]);
            }
       }
    }
    printf("%lld",totalways[(SIZE-1)][(SIZE-1)]);
    return 0;
}
