enum{ MOD = 1000000007};

int dp[105][105][3];

void update(int a, int b, int c, int d) {
    if (c > dp[a][b][0] || dp[a][b][2] == 0) {
        dp[a][b][0] = c;
        dp[a][b][1] = d;
        dp[a][b][2] = 1;
    } 
    else if (c == dp[a][b][0]) {
        dp[a][b][1] += d;
        if (dp[a][b][1] >= MOD)
            dp[a][b][1] -= MOD;
    }
}
int*pathsWithMaxScore(char**x, int xSz, int*rsz){
    memset(dp, 0, sizeof(dp));
    int n = xSz;
    dp[n - 1][n - 1][1] = 1;
    dp[n - 1][n - 1][2] = 1;
    for (int i = n - 1; i >= 0; i--)
        for (int j = n - 1; j >= 0; j--)
            if (x[i][j] != 'X' && dp[i][j][2]) {
                if (x[i][j] >= '1' && x[i][j] <= '9')
                    dp[i][j][0] += x[i][j] - '0';
                if (i)
                    update(i - 1, j, dp[i][j][0], dp[i][j][1]);
                if (j)
                    update(i, j - 1, dp[i][j][0], dp[i][j][1]);
                if (i && j)
                    update(i - 1, j - 1, dp[i][j][0], dp[i][j][1]);
            }
    int*rv=calloc(2,sizeof(int));
    rv[0]=dp[0][0][0];
    rv[1]=dp[0][0][1];
    *rsz=2;
    return rv;
}
