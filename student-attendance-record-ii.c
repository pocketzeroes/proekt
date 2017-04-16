
enum{ MOD =(int) 1e9 + 7  };
enum{ MAXN =(int) 1e5 + 10};


int dp[MAXN][2][3];
int checkRecord(int n) {
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 3; j++){
            if (j < 2)
                dp[i + 1][0][j + 1] = (dp[i + 1][0][j + 1] + dp[i][0][j]) % MOD;
            dp[i + 1][0][0] = (dp[i + 1][0][0] + dp[i][0][j]) % MOD;
            dp[i + 1][1][0] = (dp[i + 1][1][0] + dp[i][0][j]) % MOD;
        }
        for (int j = 0; j < 3; j++){
            if (j < 2)
                dp[i + 1][1][j + 1] = (dp[i + 1][1][j + 1] + dp[i][1][j]) % MOD;
            dp[i + 1][1][0] = (dp[i + 1][1][0] + dp[i][1][j]) % MOD;
        }
    }
    int ans = 0;
    for (int i = 0; i < 3; i++)
        ans = (ans + dp[n][0][i]) % MOD;
    for (int i = 0; i < 3; i++)
        ans = (ans + dp[n][1][i]) % MOD;
    return ans;
}
