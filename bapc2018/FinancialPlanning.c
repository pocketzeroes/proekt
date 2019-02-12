#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

int main(int taskF, char**bapc){
  int n;
  ll M;
  scanf("%d %lld", &n, &M);
  ll a[n];
  ll b[n];
  for(int i=0; i<n; ++i)
    scanf("%lld %lld", &a[i], &b[i]);
  ll l = 0LL, r = (M + b[0]) / a[0] + 1LL;
  while(l < r){
    ll m = (l + r) / 2LL, p = 0LL;
    for(int i=0; i<n; ++i){
      ll t = a[i] * m - b[i];
      p = min(M, max(p, p + t));
    }
    if(p < M)
      l = m + 1;
    else
      r = m;
  }
  printf("%lld\n", l);
  return 0;
}
