
static const int ky[4] = {0, -1, 0, 1};
static const int kx[4] = {1, 0, -1, 0};

int maxDistance(int**grid, int gridSz, int*grid0sz){
    int n = gridSz;
    int d[n][n];// dfill(d, n, n INT_MAX);
  for(int i=0; i<n; i++)  
    for(int j=0; j<n; j++) 
      d[i][j] = INT_MAX;     
void dfs(int y, int x){
    for (int i = 0; i < 4; ++i) {
        int yy = y + ky[i], xx = x + kx[i];
        if (yy < 0 || yy >= n || xx < 0 || xx >= n)
            continue;
        if (d[y][x] + 1 < d[yy][xx]) {
            d[yy][xx] = d[y][x] + 1;
            dfs(yy, xx);
        }
    }
}
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (grid[i][j] == 1)
                d[i][j] = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (grid[i][j] == 1)
                dfs(i, j);
    int ret = -1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (d[i][j] != 0 && d[i][j] != INT_MAX && d[i][j] > ret)
                ret = d[i][j];
    return ret;
}
