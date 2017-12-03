int max(int a,int b){return a>b?a:b;}

enum{ N = 60};
int dp[N * 2][N][N];

int cherryPickup(int**a, int aSz, int a0sz){
    int n = aSz;
    memset(dp, 255, sizeof(dp));
    dp[0][0][0] = a[0][0];
    for (int k = 1; k <= 2 * n - 2; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                int ci = k - i, cj = k - j;
                if (!(ci >= 0 && ci < n && cj >= 0 && cj < n)) 
                    continue;
                if (a[i][ci] < 0 || a[j][cj] < 0) 
                    continue;
                if (i - 1 >= 0 && j - 1 >= 0) {
                    if (dp[k - 1][i - 1][j - 1] >= 0)
                      dp[k][i][j] = max(dp[k][i][j], dp[k - 1][i - 1][j - 1] + (i == j ? a[i][ci] : a[i][ci] + a[j][cj]));
                }
                if (i - 1 >= 0 && cj - 1 >= 0) {
                    if (dp[k - 1][i - 1][j] >= 0)
                      dp[k][i][j] = max(dp[k][i][j], dp[k - 1][i - 1][j] + (i == j ? a[i][ci] : a[i][ci] + a[j][cj]));
                }
                if (ci - 1 >= 0 && j - 1 >= 0) {
                    if (dp[k - 1][i][j - 1] >= 0)
                      dp[k][i][j] = max(dp[k][i][j], dp[k - 1][i][j - 1] + (i == j ? a[i][ci] : a[i][ci] + a[j][cj]));
                }
                if (ci - 1 >= 0 && cj - 1 >= 0) {
                    if (dp[k - 1][i][j] >= 0)
                      dp[k][i][j] = max(dp[k][i][j], dp[k - 1][i][j] + (i == j ? a[i][ci] : a[i][ci] + a[j][cj]));
                }
            }
        }
    }
    int ret = dp[2 * n - 2][n - 1][n - 1];
    if (ret < 0) 
        ret = 0;
    return ret;
}
