int r,c;
int par[900];

int find(int x){
  if(par[x] == x)
    return x;
  else{
    par[x] = find(par[x]);
    return par[x];
  }
}
bool merge(int x, int y){
  x = find(x);
  y = find(y);
  if(x == y)
    return false;
  par[x] = y;
  return true;
}
int dfs(int**g){
  for(int i = 0; i < r*c; i++)
    par[i] = i;
  int ret = 0;
  for(int i = 0; i < r; i++) {
    for(int j = 0; j < c; j++) {
      ret += g[i][j];
      if(g[i][j] == 0)
        continue;
      if(i+1 < r && g[i+1][j])
        ret -= merge(i*c+j, (i+1)*c+j);
      if(j+1 < c && g[i][j+1])
        ret -= merge(i*c+j, (i)*c+j+1);
    }
  }
  return ret;
}
int minDays(int**g, int gSz, int*g0sz){
  r = gSz;
  c = g0sz[0];
  if(dfs(g) != 1)
    return 0;
  for(int i = 0; i < gSz; i++){
    for(int j = 0; j < g0sz[i]; j++){
      if(g[i][j]){
        g[i][j] = 0;
        if(dfs(g) != 1)
          return 1;
        g[i][j] = 1;
      }
    }
  }
  return 2;
}
