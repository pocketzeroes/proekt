int dp [75][75];
int ndp[75][75];

int cherryPickup(int**grid, int gridSz, int*grid0sz){
  int r = gridSz;
  int c = grid0sz[0];
  memset(dp, -1, sizeof(dp));
  dp[0][c-1] = grid[0][0] + grid[0][c-1];
  for(int i = 1; i < r; i++){
    memset(ndp, -1, sizeof(ndp));
    for(int a = 0; a < c; a++){
      for(int b = 0; b < c; b++){
        if(dp[a][b] < 0)
          continue;
        for(int na = a-1; na <= a+1; na++){
          for(int nb = b-1; nb <= b+1; nb++){
            if(fmin(na, nb) < 0 || fmax(na, nb) >= c)
              continue;
            int cand = dp[a][b] + grid[i][na];
            if(na != nb)
              cand += grid[i][nb];
            ndp[na][nb] = fmax(ndp[na][nb], cand);
          }
        }
      }
    }
    memcpy(dp, ndp, sizeof(dp));
  }
  int ret = 0;
  for(int a = 0; a < c; a++){
    for(int b = 0; b < c; b++){
      ret = fmax(ret, dp[a][b]);
    }
  }
  return ret;
}
