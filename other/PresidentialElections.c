#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}
enum{ MY_INFINITY = 1000000001};
int dp[2017];

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
inline int findMajority(int x){
  return (x / 2) + 1;
}
int main(){
  int totalDelegates = 0;
  fill(dp, 2017, MY_INFINITY);
  dp[0] = 0;
  int S;
  scanf("%d", &S);
  for(int i=0; i<S; i++){
    int D, C, F, U;
    scanf("%d %d %d %d", &D, &C, &F, &U);
    totalDelegates += D;
    int stateVoters = C + F + U;
    int majority = findMajority(stateVoters);
    int leftToConvince = max(majority - C, 0);
    if (leftToConvince > U)
      continue;
    for (int j = totalDelegates; j >= D; j--)
      dp[j] = min(dp[j], dp[j - D] + leftToConvince);
  }
  int ans = MY_INFINITY;
  int delegatesNeeded = findMajority(totalDelegates);
  for (int j = delegatesNeeded; j <= totalDelegates; j++)
    ans = min(ans, dp[j]);
  if (ans == MY_INFINITY)
    puts("impossible");
  else
    printf("%d\n", ans);
  return 0;
}
