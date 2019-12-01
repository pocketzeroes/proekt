enum{ N_MAX = 105};
enum{ INF =(int) 1e9 + 5};
int dp[N_MAX][N_MAX];

int palindromePartition(char*s, int k){
    int n = strlen(s);
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= k; j++)
            dp[i][j] = INF;
    dp[0][0] = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < k; j++)
            for(int len = 1; i + len <= n; len++) {
                int cost = 0;
                for(int a = i, b = i + len - 1; a < b; a++, b--)
                    cost += s[a] != s[b];
                dp[i + len][j + 1] = fmin(dp[i + len][j + 1], dp[i][j] + cost);
            }
    return dp[n][k];
}
