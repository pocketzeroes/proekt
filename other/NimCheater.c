#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{mod=1000000007};
/*
template<class T> int getbit(T s, int i) { return (s >> i) & 1; }
template<class T> T onbit(T s, int i) { return s | (T(1) << i); }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
template<class T> int cntbit(T s) { return __builtin_popcount(s);}
typedef unsigned long long ull;

typedef long double ld;
typedef pair<int, int> II;
typedef pair<ll, ll> LL;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
*/
typedef long long ll;

int n;
ll p[1005];

ll mu(ll x, ll k){
  if(k == 0)
    return 1;
  if(k & 1)
    return mu(x, k - 1) * x % mod;
  ll T = mu(x, k >> 1);
  return T * T % mod;
}
ll go(int c) {
  ll res = 0;
  ll POS = (1ll << c), REST = POS-1;
  ll cnt[] = {1,0}, ncnt[2];
  for(int i = 0; i < (n); ++i){
    ll a,b;
    if (p[i] & (1ll << c)){
      a = 1ll<<c;
      b = 1 + (p[i]&REST);
    }
    else {
      a = 1+(p[i]&REST);
      b = 0;
    }
    a %= mod;
    b %= mod;
    ncnt[0] = (cnt[0] * a % mod + cnt[1] * b % mod) % mod;
    ncnt[1] = (cnt[0] * b % mod + cnt[1] * a % mod) % mod;
    memcpy(cnt, ncnt, sizeof(cnt));
  }
  if (c == 0){
    res = 1;
    bool found = false;
    for(int i = 0; i < n; ++i)
      if (p[i] & 1){
        res = res * 2 % mod;
        found = true;
      }
      if(found)
        res = res * mu(2, mod - 2) % mod;
      return res;
  }
  ll sum = 0;
  for(int i = 0; i < n; ++i)
    if (p[i] & (1ll<<c))
      sum ^= 1;
  if(sum == 0){
    ll prod = 1;
    for(int i = 0; i < n; ++i)
      prod = prod * ((1 + (p[i] & REST)) % mod) % mod;
    return res = ((cnt[0] + mod - prod) % mod * mu((1ll<<c) % mod, mod - 2) + go(c-1)) % mod;
  }
  else{
    return res = cnt[0] * mu((1ll<<c) % mod, mod - 2) % mod;
  }
}
ll cal(ll*a){
  for(int i = 0; i < (n); ++i)
    p[i] = a[i];
  return go(61);
}
void solve(int itest){
  scanf("%d", &n);
  ll a[n];
  for(int i = 0; i < n; ++i)
    scanf("%lld", &a[i]);
  ll res = cal(a);
  for(int i = 0; i < (n); ++i) --a[i];
  for(int i = 0; i < (n); ++i){
    a[i]++;
    res = (res + mod - cal(a)) % mod;
    a[i]--;
  }
  res = (res + cal(a) * (n - 1) % mod) % mod;
  printf("%lld\n", res);
}
ll randN(int num){
  ll res = 0;
  for(int i = 0; i < (num); ++i) res = res * 10 + rand() % 10;
  return res + 1;
}
void gen(int itest){
  if(itest == 0){
    puts("3");
    puts("4 5 6");
  }
  else{
    if(itest <= 20){
      n = itest * 10;
      printf("%d\n", n);
      for(int i = (1); i <= (n); ++i) {
        printf("%lld", randN(3));
        if(i == n)
          puts("");
        else
          printf(" ");
      }
    }
    else{
      n = fmin(1000, itest * 25);
      printf("%d\n", n);
      for(int i = (1); i <= (n); ++i) {
        printf("%lld", randN(18));
        if(i == n)
          puts("");
        else
          printf(" ");
      }
    }
  }
}
int main(){
  for(int i = (0); i <= (0); ++i){
    solve(i);
  }
 return 0;
}
