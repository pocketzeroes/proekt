enum{ INF = (int)1E9};
int dir[5][2] = {-1,0,1,0,0,1,0,-1,0,0};

int minFlips(int**mat, int matSz, int*mat0sz){
  int n = matSz, m = mat0sz[0];
  int sz = n * m, ans = INF;
  for(int mask=(0);mask<(1<<sz);mask++){
    int G[n][m];
    for(int i=0;i<n;i++){
      for(int j=0;j<m;j++){
        G[i][j]=mat[i][j];
      }
    }
    for(int i=0;i<n;i++){
      for(int j=0;j<m;j++){
        if ((1 << (i * m + j)) & mask) {
          for(int d=(0);d<(5);d++) {
            int x = i + dir[d][0],
                y = j + dir[d][1];
            if (x < 0 || y < 0 || x >= n || y >= m)
              continue;
            G[x][y] ^= 1;
          }
        }
      }
    }
    int s = 0;
    for(int i=(0);i<(n);i++)
      for(int j=(0);j<(m);j++)
        s += G[i][j];
    if (s == 0)
      ans = fmin(ans, __builtin_popcount(mask));
  }
  return ans == INF ? -1 : ans;
}
