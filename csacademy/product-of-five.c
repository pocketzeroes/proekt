#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}



int main() {
    int N;
    scanf("%d", &N);
    int v[N];

    for (int i = 0; i < N; ++i) {
        scanf("%d", &v[i]);
    }
    int productOfFive(){
        int Max=-2140000000;
        qsort(v,N,sizeof(int),cmp);
        for(int i=0;i<=5;i++)
        {
            int Sum=1;
            for(int j=0;j<i;j++)
                Sum*=v[j];
            for(int j=0;j<5-i;j++)
                Sum*=v[N-j-1];
            Max=max(Max,Sum);
        }
        return Max;
    }
    printf("%d\n", productOfFive(v) );
    return 0;
}
