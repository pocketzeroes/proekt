int max(int a,int b){return a>b?a:b;}

int deleteAndEarn(int*a, int aSz){
    int n = 10001;
    int cnt[n];memset(cnt,0,sizeof(cnt));
    for(int i=0;i<aSz;i++){int x = a[i];
        cnt[x]++;
    }
    int dp[n];
    dp[0] = 0;
    for(int i = 1; i < n; ++i){
        dp[i] = dp[i - 1];
        int cur = i * cnt[i] + (i - 2 >= 0 ? dp[i - 2] : 0);
        dp[i] = max(dp[i], cur);
    }
    return dp[n - 1];
}
