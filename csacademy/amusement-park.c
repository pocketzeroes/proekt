#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>


double p[1000][1000];
double dp[1001][1001];

void calc(int n, int dep) {
  double x = 1.0, y = 0;
  for(int i = 0; i < (n); i++) {
    y += x;
    y += x * dp[dep - 1][(i+1) % n] * (1 - p[dep - 1][i]);
    x *= p[dep - 1][i];
  }
  dp[dep][0] = y / (1 - x);
  for (int i = n - 1; i > 0; i--) {
    double ans = 1.0 + p[dep - 1][i] * dp[dep][(i + 1) % n] + (1 - p[dep - 1][i]) * dp[dep - 1][(i + 1) % n];
    dp[dep][i] = ans;
  }
}
int main(){
  int t, a; 
  scanf("%d %d", &t, &a);
  for(int i = 0; i < (t); i++) 
    for(int j = 0; j < (a); j++) {
      int x; 
      scanf("%d", &x);
      p[i][j] = x / 100.0;
    }
  for(int i = 0; i < (t); i++) 
    calc(a, i + 1);
  double ans = dp[t][0];
  printf("%.15lf\n", ans);
  return 0;
}


















