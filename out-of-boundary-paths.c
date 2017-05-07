int f[50][50][51], ans[51];
const int MOD = 1000000007;
int nRows, nCols;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

bool valid(int r, int c) {
    return 0 <= r && r < nRows && 0 <= c && c < nCols;
}
int findPaths(int m, int n, int N, int i, int j) {
    nRows = m, nCols = n;
    memset(f, 0, sizeof(f));
    memset(ans, 0, sizeof(ans));
    if (!valid(i, j)) {
        return 1;
    }
    f[i][j][0] = 1;
    int ret = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < nRows; j++) {
            for (int k = 0; k < nCols; k++) {
                for (int l = 0; l < 4; l++) {
                    int nr = j + dx[l], nc = k + dy[l];
                    if (valid(nr, nc)) {
                        f[nr][nc][i] = (f[nr][nc][i] + f[j][k][i - 1]) % MOD;
                    } 
                    else {
                        ans[i] = (ans[i] + f[j][k][i - 1]) % MOD;
                    }
                }
            }
        }
        ret = (ret + ans[i]) % MOD;
    }
    return ret;
}
