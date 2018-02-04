
int swimInWater(int**grid, int n, int*grid0sz){
    int vis[n][n];
    void dfs(int i, int j, int v) {
        if (grid[i][j] > v) return;
        if (vis[i][j]     ) return;
        vis[i][j] = true;
        if (i + 1 < n) dfs(i + 1, j, v);
        if (j + 1 < n) dfs(i, j + 1, v);
        if (i > 0    ) dfs(i - 1, j, v);
        if (j > 0    ) dfs(i, j - 1, v);
    }
    for(int v = 0; v < n*n; v++){
        memset(vis, 0, sizeof(vis));
        dfs(0, 0, v);
        if(vis[n - 1][n - 1])
            return v;
    }
    return n*n;
}
