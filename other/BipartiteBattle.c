#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

ll bigmod(ll a, ll n, ll mod){
  if (n == 0) return 1%mod;
  if (n == 1) return a%mod;
  ll r = bigmod(a*a%mod, n/2, mod);
  if (n%2) r = r*a%mod;
  return r;
}
int main(){
  ll mod =(ll) 1e9+7;
  ll ret = 1;
  int N, total = 0;
  scanf("%d", &N);
  for(int i = 0; i < N; i++){
    ll ai, bi;
    scanf("%lld %lld", &ai, &bi);
    total ^= ((ai%2) ^ (bi%2));
    ret = ret * bigmod(2, ai*bi-(i==0), mod) % mod;
  }
  if(total)
    puts("0");
  else
    printf("%lld\n", ret);
  return 0;
}
