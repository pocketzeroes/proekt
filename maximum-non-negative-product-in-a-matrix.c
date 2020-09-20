long long f[20][20], g[20][20];
int m, n;
int maxProductPath(int**a, int aSz, int*a0sz){
    m = aSz;
    n = a0sz[0];
    int i, j, k;
    for (i = 0; i < m; ++i){
        for (j = 0; j < n; ++j){
            if (i == 0 && j == 0){
                f[i][j] = g[i][j] = a[0][0];
                continue;
            }
            if (i > 0 && j == 0) {
                f[i][j] = fmaxl(f[i-1][j] * a[i][j], g[i-1][j] * a[i][j]);
                g[i][j] = fminl(f[i-1][j] * a[i][j], g[i-1][j] * a[i][j]);
                continue;
            }
            if (i == 0 && j > 0) {
                f[i][j] = fmaxl(f[i][j-1] * a[i][j], g[i][j-1] * a[i][j]);
                g[i][j] = fminl(f[i][j-1] * a[i][j], g[i][j-1] * a[i][j]);
                continue;
            }
            f[i][j] = fmaxl(f[i-1][j] * a[i][j], g[i-1][j] * a[i][j]);
            g[i][j] = fminl(f[i-1][j] * a[i][j], g[i-1][j] * a[i][j]);
            f[i][j] = fmaxl(f[i][j-1] * a[i][j], f[i][j]);
            f[i][j] = fmaxl(f[i][j], g[i][j-1] * a[i][j]);
            g[i][j] = fminl(g[i][j], g[i][j-1] * a[i][j]);
            g[i][j] = fminl(f[i][j-1] * a[i][j], g[i][j]);
        }
    }
    long long res = f[m-1][n-1];
    if (res < 0) return -1;
    else return res % 1000000007;
}
