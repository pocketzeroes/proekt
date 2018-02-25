int numTilings(int n){
    int mod = 1000000007;
    long*dp = calloc(4, sizeof(long));
    dp[0] = 1;
    for(int i = 0;i < n;i++){
        long*ndp = calloc(4, sizeof(long));
        ndp[3] += dp[0];
        ndp[1] += dp[2];
        ndp[2] += dp[1];
        ndp[0] += dp[3];
        ndp[0] += dp[0];
        ndp[1] += dp[0];
        ndp[2] += dp[0];
        ndp[3] += dp[1];
        ndp[3] += dp[2];
        for(int j = 0;j < 4;j++)
            dp[j] = ndp[j] % mod;
        free(ndp);
    }
    int rv=(int)dp[0];
    free(dp);
    return rv;
}
