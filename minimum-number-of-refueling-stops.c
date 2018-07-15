#define max(a,b) (((a)>(b))?(a):(b))
int minRefuelStops(int target, int startFuel, int**stations, int statSz, int*statSzs){
    int dp[501][501];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = startFuel;
    int n = statSz;
    int bef = 0;
    for(int i=1; i<=n; ++i){
        int gap = stations[i-1][0]-bef;
        if (dp[i-1][0]>=gap)
            dp[i][0]=dp[i-1][0]-gap;
        for(int j=1;j<=i;++j){
            if (dp[i-1][j]>=gap) 
                dp[i][j]=max(dp[i][j],dp[i-1][j]-gap);
            if (dp[i-1][j-1]>=gap) 
                dp[i][j]=max(dp[i][j],dp[i-1][j-1]-gap+stations[i-1][1]);
        }
        bef=stations[i-1][0];
    }
    int gap=target-bef;
    for (int i=0;i<=n;++i)
        if (dp[n][i]>=gap) 
            return i;
    return -1;
}
