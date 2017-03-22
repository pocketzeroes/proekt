#define MIN(a,b) (((a)<(b))?(a):(b))

int minPathSum(int** grid, int gridRowSize, int gridColSize) {
    if (gridRowSize == 0 || gridColSize == 0)
        return 0;
    int m = gridRowSize, n = gridColSize;
    int dp[m+1][n+1];
    memset(dp,0,sizeof(dp));
    for(int i=0;i<m;i++ ){
        for(int j=0;j<n;j++ ){
            if( i == 0 && j == 0)
                dp[i][j] = grid[i][j];
            else if (i == 0)
                dp[i][j] = dp[i][j - 1] + grid[i][j];
            else if( j == 0 )
                dp[i][j] = dp[i - 1][j] + grid[i][j];
            else
                dp[i][j] = MIN(dp[i][j - 1], dp[i - 1][j]) + grid[i][j];
        }
    }
    return dp[m - 1][n - 1];
}
