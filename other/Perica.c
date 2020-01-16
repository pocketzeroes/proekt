#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
typedef long long ll;

enum{ mod =(int)(1e9) + 7};
enum{ MAXN = 1 << 17 };
enum{ MAXK = 55      };
int comb[MAXN][MAXK];
int a[MAXN];
int n, k;

int main(){
  scanf("%d %d", &n, &k);
  comb[0][0] = 1;
  for(int i = 1; i <= n; ++i)
    for(int j = 0; j <= k; ++j){
      comb[i][j] = comb[i-1][j];
      if (j > 0)
        comb[i][j] += comb[i-1][j-1];
      if (comb[i][j] >= mod)
        comb[i][j] -= mod;
    }
  for (int i = 0; i < n; ++i)
    scanf("%d", &a[i]);
  qsort(a, n, sizeof(int), cmp);
  ll ans = 0;
  for(int i = 0; i < n; ++i)
    ans = (ans + a[i] * (ll)comb[i][k-1])%mod;
  printf("%lld\n", ans);
  return 0;
}
