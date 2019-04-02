#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
ll in_nextInt(){
  ll x;
  scanf("%lld", &x);
  return x;
}
signed main(){
  ll N = in_nextInt();
  ll v[N];
  for(ll i=0; i<N; ++i)
    v[i] = in_nextInt();
  qsort(v, N, sizeof(ll), cmpLL);
  ll j=1,sum=0;
  for(ll i=N-1; i>=0; --i, ++j)
    if(j%3==0)
      sum += v[i];
  printf("%lld\n", sum);
  return 0;
}
