int       a[305][305];
long long s[305][305];

int maxSideLength(int**mat, int matSz, int*mat0sz, int threshold){
    int n = matSz;
    int m = mat0sz[0];
    memset(s, 0, sizeof s);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j){
            a[i][j] = mat[i - 1][j - 1];
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
        }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j){
            for (int k = 1; k <= i && k <= j; ++k) 
                if (s[i][j] - s[i - k][j] - s[i][j - k] + s[i - k][j - k] <= threshold)
                    ans = fmax(ans, k);
        }
    return ans;
}
