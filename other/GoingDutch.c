#include <stdio.h>

int b[20];
int dp[1 << 20];

int main(){
  for(int i = 0; i < 20; i++)
    b[i] = 0;
  int n, m;
    scanf("%d %d", &n, &m);
  while(m--){
    int x, y, p;
    scanf("%d %d %d", &x, &y, &p);
    b[x] += p, 
    b[y] -= p;
  }
  dp[0] = 0;
  for(int i = 1; i < 1 << n; ++i){
    int balance = 0, 
        best    = 1000;
    for(int j = 0; j < n; ++j){
      if(i & (1 << j)){
        if(best > dp[i ^ (1 << j)])
           best = dp[i ^ (1 << j)];
        balance += b[j];
      }
    }
    if(balance)
      dp[i] = best + 1;
    else
      dp[i] = best;
  }
  printf("%d\n", dp[(1 << n) - 1]);
  return 0;
}
