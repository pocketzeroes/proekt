#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}

typedef long long ll;
int*fact;
int*factInv;
enum{ MOD = 1000000007};

int modpow(ll b, ll e, ll m){
  ll r = 1;
  while(e > 0){
    if(e%2 == 1){
      r *= b;
      r %= m;
    }
    b *= b;
    b %= m;
    e /= 2;
  }
  return(int)r;
}
int numWays(int n, int k){
  ll ret = fact[n+k-1];
  ret *= factInv[k-1];
  ret %= MOD;
  ret *= factInv[n];
  ret %= MOD;
  return (int)ret;
}
void preprocess(){
  fact    = calloc(2100000, sizeof(int));
  factInv = calloc(2100000, sizeof(int));
  fact[0] = 1;
  for(int i = 1; i < 2100000; i++)
    fact[i] = (int)((fact[i-1] * (ll)(i)) % MOD);
  factInv[2100000-1] = modpow(fact[2100000-1], MOD-2, MOD);
  for(int i = 2100000-2; i >= 0; i--)
    factInv[i] = (int)((factInv[i+1] * (i+1LL))%MOD);
}
int main(){
  preprocess();
  int n = in_nextInt();
  int x = in_nextInt();
  int y = in_nextInt();
  ll ret = 0;
  for(int k = 1; k <= fminl(n/x, n/y); k++){
    ret += numWays(n - k*x, k) * 1LL * numWays(n - k*y, k);
    ret %= MOD;
  }
  free(fact);
  free(factInv);
  printf("%lld\n", ret);
  return 0;
}
