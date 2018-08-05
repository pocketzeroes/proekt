#define max(a,b) (((a)>(b))?(a):(b))

int projectionArea(int**grid, int gridSz, int*grid0sz){
    int n = gridSz,
        m = grid0sz[0];
    int zx = 0, yz = 0, xy = 0;
    for(int i=0; i<n; i++){
      int czx = 0, cyz = 0, cxy = 0;
      for(int j=0; j<m; j++){
        if (grid[i][j])
            cxy++;
        czx = max(czx, grid[i][j]);
        cyz = max(cyz, grid[j][i]);
      }
      zx += czx;
      yz += cyz;
      xy += cxy;
    }
    return xy + yz + zx;
}
