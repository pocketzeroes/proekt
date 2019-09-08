#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

long long exgcd(long long a, long long b, long long*x, long long*y)
{
    if(b==0)
    {
       *x=1, *y=0;
        return a;
    }
    else if(b>a)
        return exgcd(b,a,y,x);
    else
    {
        long long r=exgcd(b,a%b,x,y);
        long long temp = *x;
        *x = *y;
        *y = temp-(a/b) * (*y);
        return r;
    }
}
int main()
{
    double pt,p1,p2;
    int flag=0;
    long long m0,n0;
    scanf("%lf%lf%lf",&pt,&p1,&p2);
    long long x,y,z;
    x=ceil(pt*10000);
    y=ceil(p1*10000);
    z=ceil(p2*10000);
    long long gcd=exgcd(y,z,&m0,&n0);
    for(long long t=x*m0/z+2; t>=-1*x*n0/y-2; t--)
    {
        long long q=(x*m0-z*t)/gcd;
        long long p=(x*n0+y*t)/gcd;
        if(q>=0&&p>=0)
        {
            printf("%lld %lld\n",q,p);
            flag=1;
        }
    }
    if(flag==0)
        printf("none\n");
    return 0;
}
