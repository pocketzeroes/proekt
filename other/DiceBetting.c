#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int N, K, S;
double dp[10005][505];

void fill(double*arr, int sz, double val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int main(){
  scanf("%d %d %d", &N, &S, &K);
  dp[0][0] = 1;
  for(int i=0; i<N; i++){
    fill(dp[i+1], S, 0);
    for(int at=0; at<=S; at++)
      dp[i+1][at] += dp[i][at] * (double)at/(double)S, dp[i+1][at+1] += dp[i][at] * (double)(S-at)/(double)S;
  }
  double answer = 0;
  for(int i=K; i<=S; i++)
    answer += dp[N][i];
  printf("%.9lf\n", answer);
  return 0;
}
