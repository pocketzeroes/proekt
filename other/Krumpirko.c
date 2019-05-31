#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define min(a,b) ((a)<(b)?(a):(b))

enum{MAXN = 105    };
enum{MAXW = 505    };
enum{inf  = 1 << 30};
int n, l;
int a[MAXN];
int gc[MAXN];
int dp[MAXN][MAXN][MAXW];

int accumulate(int*arr, int sz){
  int sum=0;
  for(int i=0; i<sz; i++)
    sum += arr[i];
  return sum;
}
int f (int x, int c, int w){
  if (w < 0)
    return inf;
  if (c < 0)
    return inf;
  if (c == 0 && w == 0)
    return 0;
  if (x == n)
    return inf;
#define ret dp[x][c][w]
  if (ret != -1)
    return ret;
  ret = inf;
  return ret = min(f(x+1, c-1, w - a[x]) + gc[x], f(x+1, c, w));
  #undef ret
}
int main(){
  memset(dp, -1, sizeof dp);
  scanf("%d%d", &n, &l);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 0; i < n; ++i) scanf("%d", &gc[i]);
  int sumc = accumulate(gc, n);
  int sumw = accumulate(a , n);
  double ans = inf * 1.0 * inf;
  for (int i = 0; i < MAXW; ++i) {
    int c0 = min(f(0, n-l, i), f(0, l, i));
    if (c0 == inf) 
      continue;
    ans = min(ans, c0*1.0 / i * (sumc - c0) / (sumw - i));
  }
  printf("%.3lf\n", ans);
  return 0;
}
