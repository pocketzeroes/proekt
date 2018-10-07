#define MOD 1000000007
long long dp[105][105];

int numMusicPlaylists(int N, int L, int K) {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 0; i < L; i++)
        for (int j = 0; j <= N; j++) {
            if (j > K)
                dp[i + 1][j] = (dp[i + 1][j] + dp[i][j] * (j - K)) % MOD;
            if (j != N)
                dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j] * (N - j)) % MOD;
        }
    return dp[L][N];
}
