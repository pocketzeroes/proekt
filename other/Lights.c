#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ mod = 10567201};
typedef long long ll;
ll fact[mod];

ll modexp(ll a, ll n, int mod){
  ll r = 1;
  while (n) {
    if (n & 1) { r = (r * a) % mod; --n; }
    else { a = (a * a) % mod; n >>= 1; }
  }
  return r;
}
ll inverse(ll a) { 
  return modexp(a, mod - 2, mod); 
}
ll ncr(ll m, ll n) {
  if (m < n) return 0;
  return (fact[m] * inverse((fact[n] * fact[m - n]) % mod)) % mod;
}
ll calc(ll n, ll m, bool iszero) {
  ll pow2n = modexp(2, n, mod),
     invpow2n = inverse(pow2n);
  if (m & 1) return (ncr(pow2n, m) * invpow2n) % mod;
  else {
    ll inv2 = inverse(2);
    ll dif = ncr((pow2n * inv2) % mod, m / 2);
    if (m & 2) dif = (mod - dif) % mod;
    ll res1 = ((ncr(pow2n, m) + mod - dif) * invpow2n) % mod;
    return iszero ? (dif + res1) % mod : res1;
  }
}
int main() {
  ll n, m, v;
  fact[0] = 1;
  for (n = 1; n < mod; ++n)
    fact[n] = (n * fact[n - 1]) % mod;
  while (scanf("%lli%lli%lli", &n, &m, &v) == 3 && n)
    printf("%lli\n", calc(n, m, v == 0));
  return 0;
}
