#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>


long long b,x,y,A,S,K;
int main() 
{
    scanf("%lld %lld %lld %lld %lld", &A, &S, &K, &x, &y);
    if((S-A+K*y)%(x+y)!=0)
    {
        puts("-1");
        return 0;
    }
    b=(S-A+K*y)/(x+y);
    if(b>K)
    {
        puts("-1");
        return 0;
    }
    printf("%lld\n",b);
    return 0;
}
