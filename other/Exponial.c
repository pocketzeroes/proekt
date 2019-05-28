#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

ll phi(ll m){
  ll res = 1;
  for (ll p = 2; p*p <= m; ++p) {
    if (m % p == 0) {
      res *= p-1;
      m /= p;
      while (m % p == 0) {
        res *= p;
        m /= p;
      }
    }
  }
  if (m > 1)
    res *= m-1;
  return res;
}
ll expmod(ll b, ll e, ll m){
  ll res = 1;
  while (e) {
    if (e & 1)
      res = (res * b) % m;
    e /= 2;
    b = (b*b) % m;
  }
  return res;
}
ll expo_trunc(ll n){
  return n < 4 ? n < 3 ? n : 9 : 100000;
}
ll expo_mod_m(ll n, ll m){
  if (m == 1)
    return 0;
  if (n == 1)
    return 1;
  ll m2 = phi(m), e = expo_trunc(n-1);
  if (e == 100000)
    e = m2 + expo_mod_m(n-1, m2);
  return expmod(n, e, m);
}
int main(){
  int n, m;
  while (scanf("%d%d", &n, &m) == 2)
    printf("%lld\n", expo_mod_m(n, m));
  return 0;
}
