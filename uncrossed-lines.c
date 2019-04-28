int max(int a,int b){return a>b?a:b;}

int maxUncrossedLines(int*a, int aSz, int*b, int bSz){
  int n = aSz,
      m = bSz;
  int dp[n+1][m+1]; memset(dp, 0, sizeof(dp));
  dp[0][0] = 0;
  for(int i = 1; i < n+1; i++){
    for(int j = 1; j < m+1; j++){
      if(a[i-1] == b[j-1])
        dp[i][j] = dp[i-1][j-1] + 1;
      else
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    }
  }
  return dp[n][m];
}
