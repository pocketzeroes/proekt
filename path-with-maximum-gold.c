int cur;
int ans;
int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void dfs(int**grid, int m, int n, int i, int j){
    cur += grid[i][j];
    grid[i][j] = -grid[i][j];
    ans = fmax(ans, cur);
    for (int k = 0; k < 4; ++k) {
        int i0 = i + dirs[k][0];
        int j0 = j + dirs[k][1];
        if (i0 >= 0 && i0 < m && j0 >= 0 && j0 < n && grid[i0][j0] > 0)
            dfs(grid, m, n, i0, j0);
    }
    cur += grid[i][j];
    grid[i][j] = -grid[i][j];
}
int getMaximumGold(int**grid, int gridSz, int*grid0sz){
    int m = gridSz;
    int n = grid0sz[0];
    ans = 0;
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            cur = 0;
            if (grid[i][j] > 0)
                dfs(grid, m, n, i, j);
        }
    }
    return ans;
}
