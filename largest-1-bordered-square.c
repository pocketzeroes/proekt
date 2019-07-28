int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
enum{ N = 105};

int sum[N][N];

int get(int x1, int y1, int x2, int y2) {
    return sum[x2 + 1][y2 + 1] - sum[x1][y2 + 1] - sum[x2 + 1][y1] + sum[x1][y1];
}
int largest1BorderedSquare(int**grid, int gridSz, int*grid0sz){
    memset(sum,0,sizeof(sum));
    int n = gridSz;
    int m = grid0sz[0];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] + (grid[i][j]) - sum[i][j];
    for (int len = min(n, m); len >= 1; --len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            for (int j = 0; j + len - 1 < m; ++j) {
                if (get(i, j, i + len - 1, j) == len && get(i, j, i, j + len - 1) == len && get(i, j + len - 1, i + len - 1, j + len - 1) == len && get(i + len - 1, j, i + len - 1, j + len - 1) == len) {
                    return len * len;
                }
            }
        }
    }
    return 0;
}
