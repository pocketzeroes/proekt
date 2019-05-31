#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}

const ll MOD = 1000000007;
ll memo[10001][101];        
int n, w, h;

int main(){
  scanf("%d %d %d", &n, &w, &h);
  for (int nn = 0; nn <= n; nn++)
    memo[nn][0] = 1;
  for (int ww = 0; ww <= w; ww++)
    memo[0][ww] = 1;
  for (int nn = 1; nn <= n; nn++)
    memo[nn][1] = min(h, nn) + 1;
  for (int ww = 2; ww <= w; ww++) {
    for (int nn = 1; nn <= n; nn++) {
      memo[nn][ww] = (memo[nn-1][ww] + memo[nn][ww-1]) % MOD;
      if (nn - (h+1) >= 0)
        memo[nn][ww] = (memo[nn][ww] - memo[nn - (h+1)][ww-1]) % MOD;
    }
  }
  ll temp = min(h, n/w) + 1;
  ll ans = memo[n][w] - temp;
  if (ans < 0)
    ans += MOD;
  printf("%lld\n", ans);
  return 0;
}
