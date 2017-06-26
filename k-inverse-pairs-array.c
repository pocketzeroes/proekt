int dp[1005][2005];

enum{ MOD =(int) 1e9+7};
int kInversePairs(int n, int k) {
    memset(dp, 0, sizeof(dp));
    dp[1][0] = 1;
    for(int i=2;i<=n;i++) {
        int v = 0;
        for(int u=0;u<=k;u++) {
            v += dp[i-1][u];
            if(v>=MOD) v -= MOD;
            if(u>=i) { v = v + (MOD - dp[i-1][u-i]); v %= MOD; }    
            dp[i][u] = v;
        }
    }
    return dp[n][k];
}
