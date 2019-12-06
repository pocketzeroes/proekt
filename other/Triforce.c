#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;
ll MOD =(ll)1e6+9;

int main(){
  int N;
  scanf("%d", &N);
  ll dp[N]; clr(dp);
  dp[0] = 1;
  for(int i=0; i<N; ++i){
    if(i + 1 < N)dp[i + 1] = (dp[i+1] + 2 * dp[i]) % MOD;
    if(i  ==   0)dp[i + 1] = (dp[i+1] +     dp[i]) % MOD;
    if(i+2  == N)dp[i + 1] = (dp[i+1] +     dp[i]) % MOD;
    if(i + 2 < N)dp[i + 2] = (dp[i+2] + 4 * dp[i]) % MOD;
    if(i + 3 < N)dp[i + 3] = (dp[i+3] + 2 * dp[i]) % MOD;
  }
  printf("%lld\n", dp[N-1]);
  return 0;
}
