#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

double min(double a, double b){return a<b?a:b;}
double max(double a, double b){return a>b?a:b;}

int cmp (const void *pa, const void *pb){
    double*a=(double*)pa;
    double*b=(double*)pb;
    return *a < *b ? -1 : 1;
}


double v1[100010], v2[100010];

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf", &v1[i], &v2[i]);
    qsort(v1+1, n, sizeof(double), cmp);
    qsort(v2+1, n, sizeof(double), cmp);
    double s1=0, s2=0, sol=0;
    int c=0, l=n;
    for(int i=n; i>=1; i--)
    {
        s1 += v1[i];
        c++;
        sol = max(sol,min(s1-c,s2-c));
        while(l>=1 && s2-c<s1-c)
        {
            s2 += v2[l];
            c++;
            sol = max(sol,min(s1-c,s2-c));
            l--;
        }
    }
    printf("%.4f", sol);
    return 0;
}

