int min(int a,int b){return a<b?a:b;}
enum{ INF = (int)1E9};
int dp[100005];

int minCostClimbingStairs(int*cost, int costSz){
  int n = costSz;
  for(int i=(0);i<(n+1);i++)
    dp[i] = INF;
  dp[0] = dp[1] = 0;
  for(int i=(2);i<(n+1);i++){
    if (i-1 >= 0) dp[i] = min(dp[i], dp[i-1] + cost[i-1]);
    if (i-2 >= 0) dp[i] = min(dp[i], dp[i-2] + cost[i-2]);
  }
  return dp[n];
}
