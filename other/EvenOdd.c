#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

enum{ MOD = 1000000007};
enum{ N=101};
ll binom[N][N];

void mkbinoms(){
  binom[0][0]=1;
  for (int i=1;i<N;++i) {
    binom[i][0]=binom[i][i]=1;
    for (int j=1;j<i;++j) {
      binom[i][j]=(binom[i-1][j-1]+binom[i-1][j])%MOD;
    }
  }
}
ll range(int n, int base){
  ll ret=0;
  for (int i=0;i<=n;++i) {
    ret+=binom[n][i]*(base+i);
  }
  return ret;
}
ll s(ll x){
  if (x==0)
    return 0;
  int leftmostone=63-__builtin_clzll(x);
  int rightmostone=__builtin_ffsll(x)-1;
  if (leftmostone==rightmostone){
    return (rightmostone+s(x-1)) % MOD;
  }
  else{
    ll y = x^(1ll<<rightmostone);
    int middlezeros=leftmostone-rightmostone+1-__builtin_popcountll(x);
    return (s(y)+range(rightmostone,leftmostone+middlezeros+2)) % MOD;
  }
}
int main() {
  mkbinoms();
  ll a, b;
  scanf("%lld %lld", &a, &b);
  printf("%lld\n", (s(b) + MOD - s(a-1)) % MOD );
  return 0;
}
