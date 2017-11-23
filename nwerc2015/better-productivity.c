#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
typedef struct{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first == b->first)return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
}

const int oo = 1<<30;
int N, best[220][220][220];
pair ival[220];

int Best(int i, int P, int r){
    if (P == 0 || i == N)
        return i < N || P || r < oo ? -oo : 0;
    if (r == oo)
        r = i;
    if (ival[r].second <= ival[i].first)
        return -oo;
#define res best[i][P][r]
    int nr = ival[i].second < ival[r].second ? i : r;
    if (res == -1)
        res = max(Best(i+1, P, nr),
                  max(ival[i].second-ival[i].first + Best(i+1, P-1, r),
                      ival[nr].second-ival[i].first + Best(i+1, P-1, oo)));
    return res;
#undef res
}
int main(void){
    int P;
    scanf("%d %d", &N, &P);
    for (int i = 0; i < N; ++i)
        scanf("%d %d", &ival[i].first, &ival[i].second);
    qsort(ival, N, sizeof(pair), cmpP);
    memset(best, -1, sizeof(best));
    printf("%d\n", Best(0, P, oo));
    return 0;
}



