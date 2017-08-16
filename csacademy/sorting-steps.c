#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

inline int max(int a,int b){return a>b?a:b;}

typedef struct pair{
    int first;
    int second;
}pair;
inline pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  return a->second - b->second;
}


int main()
{
    int n;
    scanf("%d", &n);
    pair p[n];
    for(int i=0; i<n; i++){
        int ai;
        scanf("%d", &ai);
        p[i] = newPair(ai, i);
    }
    qsort(p, n, sizeof(pair), cmpP);
    int Ans=0;
    for(int i=0; i<n; i++){
        int t = (p[i].second - i);
        Ans = max(Ans, t);
    }
    printf("%d\n", Ans+1);
    return 0;
}





















