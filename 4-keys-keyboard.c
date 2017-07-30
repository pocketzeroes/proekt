int max(int a,int b){return a>b?a:b;}

int maxA(int n) {
    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
        dp[i] = max(dp[i], i);
        for (int j = i + 1; j <= n; ++j) 
            dp[j] = max(dp[j], dp[i] + j - i);
        for (int j = i + 3, k = dp[i]; j <= n; ++j, k += dp[i]) 
            dp[j] = max(dp[j], dp[i] + k);
    }
    return dp[n];
}
