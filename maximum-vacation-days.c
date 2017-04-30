int max(int a,int b){return a>b?a:b;}
enum{ N = 200};
int dp[N][N];

int maxVacationDays(int**a, int aSz, int a0Sz, int**b, int bSz, int b0Sz){
    int n = aSz, m = b0Sz;
    for (int i = 0; i < n; ++i) a[i][i] = 1;
    for (int i = 0; i < n; ++i) {
        dp[m - 1][i] = b[i][m - 1];
    }
    for (int k = m - 2; k >= 0; --k) {
        for (int i = 0; i < n; ++i) {
            dp[k][i] = 0;
            for (int j = 0; j < n; ++j) {
                if (a[i][j]) {
                    dp[k][i] = max(dp[k][i], dp[k + 1][j]);
                }
            }
            dp[k][i] += b[i][k];
        }
    }
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        if (a[0][i]) {
            ret = max(ret, dp[0][i]);
        }
    }
    return ret;
}
