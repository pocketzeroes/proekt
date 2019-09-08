#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmpDbl(const void*pa, const void*pb){
  double*a =(double*)pa;
  double*b =(double*)pb;
  return(*a < *b)?-1:1;
}
int main()
{
    int n;
    int cx,cy;
    double a[100];
    scanf("%d%d%d",&cx,&cy,&n);
    int num=0;
    for(int i=0; i<n; i++)
    {
        int x,y,r;
        scanf("%d%d%d",&x,&y,&r);
        a[i]=sqrt((cx-x)*(cx-x)+(cy-y)*(cy-y))-r;
        if(a[i]<0)
            num++;
    }
    qsort(a, n, sizeof(double), cmpDbl);
    if(num>=3)printf("0\n");
    else
        printf("%d\n",(int)a[2]);
    return 0;
}
