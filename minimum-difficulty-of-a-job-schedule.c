#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)
int minDifficulty(int*a, int aSz, int d){
    if(d > aSz)
        return -1;
    int n = aSz;
    enum{INF =(int)1e9};
    int dp[n][d+1]; dfill(dp, n, d+1, INF);
    for(int i=0; i<n; ++i){
        int diff = a[i];
        for(int j = i; j >= 0; --j){
            diff = fmax(diff, a[j]);
            if(j == 0)
                dp[i][1] = diff;
            else{
                for(int k = 2; k <= d; ++k)
                    dp[i][k] = fmin(dp[i][k], diff + dp[j - 1][k - 1]);
            }
        }
    }
    return dp[n-1][d];
}
