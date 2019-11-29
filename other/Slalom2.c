#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
typedef long long ll;
int W,vh,N;
int xs[100000],ys[100000];
int S;
int ss[1000000];

int main(){
  scanf("%d %d %d", &W, &vh, &N);
  for(int i=(0);i<(N);++i)
    scanf("%d%d",&xs[i],&ys[i]);
  scanf("%d",&S);
  for(int i=(0);i<(S);++i)
    scanf("%d",&ss[i]);
  qsort(ss, S, sizeof(int), cmp);
  int lo = -1,
      hi = S;
  while(lo+1 < hi){
    int mid = (lo+hi)/2;
    ll s = ss[mid];
    ll l = 0, r = 200000000 * s;
    ll y = 0;
    bool ok = 1;
    for(int i=0; i<N; ++i){
      l -= (ll)(ys[i]-y) * vh;
      r += (ll)(ys[i]-y) * vh;
      if(l<xs[i]*s)
        l = xs[i]*s;
      if(r>(xs[i]+W)*s)
        r = (xs[i]+W)*s;
      if(r < l){
        ok = 0;
        break;
      }
      y = ys[i];
    }
    if(ok)
      lo = mid;
    else
      hi = mid;
  }
  if (lo==-1)
    printf("IMPOSSIBLE\n");
  else
    printf("%d\n", ss[lo]);
  return 0;
}
