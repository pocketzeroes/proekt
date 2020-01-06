#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

enum{ MAXN = 1000100};
enum{ siz = 1<<20   };
typedef long long ll;
int n;
pair lis[MAXN];
int order[MAXN];
int hea[siz * 2];
ll  ans;

int main(){
  scanf("%d", &n);
  for(int i=0; i<n; ++i){
    scanf("%d", &lis[i].first);
    lis[i].second = i;
  }
  qsort(lis, n, sizeof(pair), cmpP);
  for(int i=0; i<n; ++i)
    order[lis[i].second] = n - 1 -i;
  ans = 0;
  memset(hea, 0, sizeof(hea));
  for(int i=0; i<n; ++i){
    int p = order[i] + siz;
    while(p){
      if(p % 2)
        ans += (ll)(hea[p-1]);
      hea[p]++;
      p /= 2;
    }
  }
  printf("%lld\n", ans);
  return 0;
}
