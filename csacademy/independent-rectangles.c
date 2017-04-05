#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

typedef struct pair{
    long first;
    long second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
int cmp (const void * pa, const void * pb)
{
    pair*a=(pair*)pa; pair*b=(pair*)pb;
    if(a->first > b->first ) return -1;
    if(a->first < b->first ) return  1;
    if(a->second< b->second) return -1;
    if(a->second> b->second) return  1;
    return 1;
}
int main()
{
    long n;
    scanf("%ld", &n);
    pair cor[n];
    for(long i=0; i<n; i++)
        scanf("%ld %ld", &cor[i].first, &cor[i].second);
    qsort(cor, n, sizeof(pair), cmp);
    long br=1;
    long mw=cor[0].first, mh=cor[0].second;
    for(long i=1; i<n; i++)
    {
        if(cor[i].first<=mw&&cor[i].second>=mh)
        {
            br++;
            mw=cor[i].first;
            mh=cor[i].second;
        }
    }
    printf("%ld",br);
}



