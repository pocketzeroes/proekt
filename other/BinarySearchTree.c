#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ maxn = 300000};
ll n, i, x, k;
bool bio[maxn+1];
ll depth[maxn+1];
ll prev [maxn+1];
ll next [maxn+1];
ll zbr;

int main(){
  scanf("%lld", &n);
  next[0] = n+1;
  prev[n+1] = 0;
  bio[0] = true;
  bio[n+1] = true;
  depth[0] = -1;
  depth[n+1] = -1;
  zbr = 0;
  for(int i=1; i<=n; i++){
    scanf("%lld", &x);
    k = 1;
    while(!bio[x-k] && !bio[x+k])
      k++;
    if(bio[x-k]){
      prev[x] = x-k;
      next[x] = next[x-k];
    }
    if(bio[x+k]){
      next[x] = x+k;
      prev[x] = prev[x+k];
    }
    prev[next[x]] = x;
    next[prev[x]] = x;
    bio[x] = true;
    depth[x] = 1ll + fmaxl(depth[prev[x]], depth[next[x]]);
    zbr = zbr + depth[x];
    printf("%lld\n", zbr);
  }
  return 0;
}
