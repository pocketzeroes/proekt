#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
/*
template<class T> int getbit(T s, int i) { return (s >> i) & 1; }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> II;
typedef pair<ll, ll> LL;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
*/

static inline int onbit(int s, int i){return s|((int)(1) << i);}
static inline int cntbit(int s){ return __builtin_popcount(s);}

typedef long long ll;
ll f[20][1 << 10], F[20][1 << 10], C[11][11];
int test;
ll A, B, k, d;


ll mu(ll x, ll k){
 if(k == 0)
   return 1;
 if(k & 1)
   return mu(x, k - 1) * x % 1000000007;
 ll T = mu(x, k >> 1);
 return T * T % 1000000007;
}
ll add(ll x, ll y){
  ll res = (x + y);
  if(res >= 1000000007)
    res -= 1000000007;
  return res;
}
ll sub(ll x, ll y){
  ll res = (x - y);
  if(res < 0)
    res += 1000000007;
  return res;
}
void init(){
  memset(f, 0, sizeof(f));
  memset(F, 0, sizeof(F));
  F[0][0] = 1;
  for(int i = 0; i < (10); ++i)
    f[1][1 << i] = 1;
  for(int i = 2; i <= 18; i++){
    for(int j = 0; j < i; j++)
      for(int mask = 0; mask < (1 << 10); ++mask){
        int x = mask;
        if(j < i - 1)
          x = onbit(x, 0);
        F[i - 1][x] = add(F[i - 1][x], f[j][mask]);
      }
    for(int j = (1); j <= (9); ++j) for(int mask = 0; mask < (1 << 10); ++mask){
      int x = onbit(mask, j);
      f[i][x] = add(f[i][x], F[i - 1][mask]);
    }
  }
  memset(C, 0, sizeof(C));
  for(int i = 0; i < (11); ++i)
    C[0][i] = 1;
  for(int i = (1); i <= (10); ++i)
    for(int j = (1); j <= (i); ++j)
      C[j][i] = add(C[j - 1][i - 1], C[j][i - 1]);
}
ll calA(ll x, int k){
  ll res = 1;
  for(int i = 0; i < k; i++){
    ll A = (x - i) % 1000000007;
    if(A >= 1000000007)
      A -= 1000000007;
    res = res * A % 1000000007;
  }
  return res;
}
ll*cal(ll x){
  int a[22], m = 0;
  ll*res = calloc(1<<10, sizeof(ll));
  if(x == 0)
    a[++m] = 0;
  while(x){
    a[++m] = x % 10;
    x /= 10;
  }
  int run = 0;
  for(int i = 1; i < m; i++)
    for(int mask = 0; mask < (1 << 10); ++mask)
      res[mask] = add(res[mask], f[i][mask]);
  for(int i = m; i >= 1; i--){
    int start = 0;
    if(i == m && i > 1)
      start = 1;
    for(int j = start; j < a[i]; j++){
      int M = onbit(run, j);
      for(int mask = 0; mask < (1 << 10); ++mask){
        int MM = (M | mask);
        res[MM] = add(res[MM], F[i - 1][mask]);
      }
    }
    run = onbit(run, a[i]);
  }
  res[run]++;
  return res;
}
ll sol(){
  ll*V1 = cal(B);
  ll*V2 = cal(A - 1);
  ll*V  = calloc(1<<10, sizeof(ll));
  for(int mask = 0; mask < (1 << 10); ++mask) {
    V[mask] = sub(V1[mask], V2[mask]);
    for(int mask1 = mask; mask1 > 0; mask1 = mask & (mask1 - 1)){
      int x = mask ^ mask1;
      V[x] = add(V[x], V[mask]);
    }
  }
  ll res = 0;
  ll mul = 1;
  for(int i = (1); i <= (k); ++i) 
    mul = mul * i % 1000000007;
  mul = mu(mul, 1000000007 - 2);
  for(int mask = 0; mask < (1 << 10); mask++){
    int num = cntbit(mask);
    ll so = V[mask];
    if(num >= d){
      ll need = calA(so, k) * mul % 1000000007 * C[d][num] % 1000000007;
      if((num - d) % 2 == 0) 
        res = add(res, need);
      else 
        res = add(res, 1000000007 - need);
    }
  }
  return res;
}
void solve(){
  init();
  scanf("%d", &test);
  for(int itest = 0; itest < test; ++itest){
    scanf("%lld %lld %lld %lld", &A, &B, &k, &d);
    printf("%lld\n", sol());
  }
}
int main(){
  solve();
  return 0;
}
