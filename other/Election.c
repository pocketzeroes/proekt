#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

ll binom[51][51];

void solve(){
  ll N, v1, v2, W;
  scanf("%lld %lld %lld %lld", &N, &v1, &v2, &W);
  ll sum = 0;
  int rem = N - v1 - v2;
  for (int r = 0; r <= rem; r++)
    if (v1 + r > N/2)
      sum += binom[rem][r];
  if (sum == 0)
    puts("RECOUNT!");
  else if (sum *100 > (W << rem) )
    puts("GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!");
  else
    puts("PATIENCE, EVERYONE!");
}
int main(){
  for (int n = 0; n <= 50; n++) {
    binom[n][n] = binom[n][0] = 1;
    for (int k = 1; k < n; k++) {
      binom[n][k] = binom[n-1][k] + binom[n-1][k-1];
    }
  }
  int T;
  scanf("%d", &T);
  while(T--)
    solve();
  return 0;
}
