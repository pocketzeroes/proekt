#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int n;
int a[1500][1500];
int memo[1500][1500];

int dp(int l, int r) {
  if (memo[l][r])
    return memo[l][r];
  int next = fmax(l, r) + 1;
  if (next == n)
    return 0;
  return memo[l][r] = fmin(a[next][l] + dp(next, r), a[r][next] + dp(l, next));
}
int main (){
  scanf("%d", &n);
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
      scanf("%d", &a[i][j]);
  printf("%d\n", dp(0, 0));
  return 0;
}
