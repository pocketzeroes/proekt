void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int**shiftGrid(int**g, int gSz, int*g0sz, int k, int*rsz, int**csz){
    int n = gSz;
    int m = g0sz[0];
    while(k--){
        int a[n][m];
        for(int i=0; i<n; ++i){
          for(int j=0; j<m; ++j){
            a[i][j] = g[i][j];
          }
        }
        for(int i=0; i<n; ++i){
            for(int j=0; j<m; ++j){
                if(i == n-1 && j == m-1)
                    g[0][0] = a[i][j];
                else if(j == m-1)
                    g[i+1][0] = a[i][j];
                else
                    g[i][j+1] = a[i][j];
            }
        }
    }
    int*cols=calloc(n, sizeof(int));
    fill(cols, n, m);
   *csz = cols;
   *rsz = n;
    return g;
}
