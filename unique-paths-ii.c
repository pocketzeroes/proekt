int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridRowSize, int obstacleGridColSize){
    int m = obstacleGridRowSize;
    int n = obstacleGridColSize;
    int v[n+1];
    memset(v,0,sizeof(v));
    v[0] = 1;
    for(int i = 0; i < m; ++i) {
        if(obstacleGrid[i][0] != 0)
            v[0] = 0;
        for(int j = 1; j < n; ++j) {
            if(obstacleGrid[i][j] == 0)
                v[j] += v[j - 1];
            else
                v[j] = 0;
        }
    }
    return v[n - 1];
}
