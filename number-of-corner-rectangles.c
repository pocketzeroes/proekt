
int cnt[205][205];

int countCornerRectangles(int**g, int gSz, int g0sz){
  int n = gSz, m = g0sz;
  memset(cnt, 0, sizeof(cnt));
  int ans = 0;
  for(int i=(0); i<(n); i++) {
    for(int j1=(0); j1<(m); j1++) {
      for(int j2=(j1+1); j2<(m); j2++) {
        if (g[i][j1] && g[i][j2])
          ans += cnt[j1][j2];
      }
    }
    for(int j1=(0);j1<(m);j1++) {
      for(int j2=(j1+1);j2<(m);j2++) {
        if (g[i][j1] && g[i][j2])
          cnt[j1][j2]++;
      }
    }
  }
  return ans;
}
