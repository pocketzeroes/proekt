#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main()
{
    int n, c, x1, u, x2, k=0;
    scanf("%d %d %d %d %d", &n, &c, &x1, &u, &x2);
    int ans = 0;
    int ss = n;
    for(int d = 1;d<=n;++d)
    {
        if(c >= u)
        {
            if(c - u + (n-d+1)*(x1 + (k+1)*x2) > c + (n-d+1)*(x1 + k*x2)) 
                c-=u, k++;
        }
        c+=(x1+k*x2);
    }
    printf("%d", c);
    return 0;
}
