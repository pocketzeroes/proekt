#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int L, S;
ll Modulus = 123456789ll;
ll dp[1234567];

void DP(){
  ll sumoflastSvalues = 1;
  dp[0] = 1;
  for(int d = 1; d <= L; d++){
    dp[d] = sumoflastSvalues;
    sumoflastSvalues += dp[d] + Modulus;
    if(d-S >= 0)
      sumoflastSvalues -= dp[d-S];
    sumoflastSvalues %= Modulus;
  }
}
void doit(){
  scanf("%d %d", &L, &S);
  DP();
  ll ans = 0;
  for (int l = 1; l <= S; l++){
    ans += dp[L-l] * l;
    ans %= Modulus;
  }
  printf("%lld\n", ans);
}
int main(){
  int T = 1;
  for(int t = 1; t <= T; t++)
    doit();
  return 0;
}
