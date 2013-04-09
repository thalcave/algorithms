#include <iostream>

int m[30000],a[21];

int main()
{
    int t,N,M,i,j;
    scanf("%d",&t);
    
    while(t--)
    {
        scanf("%d%d",&N,&M);
        for (i=0;i<N;i++)
            scanf("%d",&a[i]);
        for (i=0;i<=M;i++)
            m[i]=0;
        m[0]=1;
        for(i=0; i<N; i++)
            for(j=M; j>=a[i]; j--)
                m[j] |= m[j-a[i]];
        if (m[M])
           printf("Yes\n");
       else
           printf("No\n");
    }
}
