#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int minFallingPathSum(int**arr, int arrSz, int*arr0sz){
    int m = arrSz,
        n = arr0sz[0];
    int f[m][n]; clr(f);
    for(int j=0; j<n; ++j)
        f[0][j] = arr[0][j];
    for(int i=1; i<m; ++i){
        for(int j=0; j<n; ++j){
            f[i][j] = INT_MAX;
            for(int k=0; k<n; ++k){
                if(j != k)
                   f[i][j] = fmin(f[i][j], f[i - 1][k]);
            }
            f[i][j] += arr[i][j];
        }
    }
    int ans = INT_MAX;
    for (int j = 0; j < n; ++j)
        ans = fmin(ans, f[m - 1][j]);
    return ans;
}
