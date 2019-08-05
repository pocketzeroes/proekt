#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

enum{ MAXN = 22};
enum{ MAX = 500};
enum{ MOD =(int)1e9};
int n, res, tot[MAXN][MAXN], p2[MAX];

int gcd(int a, int b){
  return (b == 0) ? a : gcd(b, a % b);
}
int main(){
  scanf("%d",&n);
  p2[0] = 1;
  for (int i = 1; i < MAX; ++i)
    p2[i] = p2[i - 1] * 2 % MOD;
  for (int a = 1; a <= n; ++a)
    for (int b = a + 1; b <= n; ++b) 
      for (int i = a; i <= b; ++i)
  for (int j = i + 1; j <= b; ++j)
    if (gcd(i, j) == 1)
      ++tot[a][b];
  for (int mask = 0; mask < (1 << (n - 1)); ++mask) {
    int prev = 1, curr = 1;
    for (int x = 1; x < n; ++x)
      if (mask & (1 << (x - 1))){
        curr = (ll)curr * p2[tot[prev][x]] % MOD;
        prev = x + 1;
      }
    curr = (ll)curr * p2[tot[prev][n]] % MOD;
    res += __builtin_popcount(mask) % 2 == 0 ? curr : -curr;
    res %= MOD;
  } 
  res += MOD;
  res %= MOD;
  printf("%d\n",res);
  return 0;
}
