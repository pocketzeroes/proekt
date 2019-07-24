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

const ll maxans = 100000000000000001LL;

ll gcd(ll a, ll b){
  return b ? gcd(b, a % b) : a;
}
ll lcm(ll a, ll b){
  return a / gcd(a, b) * b;
}
int n, mod, v[10];
ll wtbl[20000][5];

ll ways_brute(int c, int x){
  if (x < 0)
    return 0;
  if (c == 0)
    return x % v[0] == 0;
  if (wtbl[x][c-1] == -1)
    wtbl[x][c-1] = ways_brute(c-1, x) + ways_brute(c, x-v[c]);
  return wtbl[x][c-1];
}
ll ways(ll x){
  int r = x % mod;
  ll k = x / mod, res = 0;
  if (k < n)
    return ways_brute(n-1, x);
  for (int i = 0; i < n; ++i) {
    ll num = ways_brute(n-1, r + mod*i), den = 1, d;
    for (int j = 0; j < n; ++j) {
      if (i != j){
        num *= k-j;
        den *= i-j;
        d = gcd(llabs(num), llabs(den));
        num /= d;
        den /= d;
      }
    }
    if (den < 0)
      num = -num, den = -den;
    assert(den == 1);
    res += num;
  }
  return res;
}
int main(){
  int cse = 0, q;
  while (scanf("%d", &n) == 1 && n){
    printf("Set %d\n", ++cse);
    mod = 1;
    for (int i = 0; i < n; ++i) {
      scanf("%d", v+i);
      mod = lcm(mod, v[i]);
    }
    memset(wtbl, -1, sizeof(wtbl));
    scanf("%d", &q);
    for (int i = 0; i < q; ++i){
      ll res = maxans, P;
      scanf("%lld", &P);
      for (int i = 0; i < *v; ++i){
        ll lo = -1,
           hi = 2;
        while ((lo+1) * *v + i < res && ways(hi * *v + i) < P)
          lo = hi, hi <<= 1;
        if ((lo+1) * *v + i >= res)
          continue;
        while (hi - lo > 1) {
          ll m = (lo + hi)/2, w = ways(m * *v + i);
          if (w < P)
            lo = m;
          else
            hi = m;
        }
        if (hi * *v + i == 0)
          ++hi;
        res = min(res, hi * *v + i);
      }
      if (res == maxans)
        printf("no candy for you\n");
      else
        printf("%lld\n", res);
    }
  }
  return 0;
}
