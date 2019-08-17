#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)

typedef struct{
  int first;
  int second;
}pair;

int p_size;

inline int idet4(int x1, int y1, int x2, int y2) {
  return x1 * y2 - x2 * y1;
}
inline int idet(int x1, int y1, int x2, int y2, int x3, int y3) {
  return idet4(x2 - x1, y2 - y1, x3 - x1, y3 - y1);
}
inline int winding_number(pair*p, int x, int y){
  int wn = 0, s = p_size;
  for (int i = 0; i < s; ++i) {
    if (p[i].second - y < 0 && p[(i+1)%s].second - y >= 0) {
      if (idet(p[i].first - x, p[i].second - y,
        p[(i+1)%s].first - x, p[(i+1)%s].second - y,
        0, 0) > 0) wn++;
    }
    else if (p[i].second - y >= 0 && p[(i+1)%s].second - y < 0) {
      if (idet(p[i].first - x, p[i].second - y, p[(i+1)%s].first - x, p[(i+1)%s].second - y, 0, 0) < 0)
        wn--;
    }
  }
  return wn;
}
int main(){
  while (1){
    int N;
    scanf("%d", &N);
    if (N == 0)
      break;
    pair p[N];
    p_size=N;
    for(int i=0; i < N; ++i){
      int x, y;
      scanf("%d %d", &x, &y);
      x += 100;
      y += 100;
      x *= 2;
      y *= 2;
      p[i] = (pair){x, y};
    }
    bool fr[200][200]; dfill(fr, 200, 200, true);
    int  wn[200][200]; memset(wn, 0, sizeof(wn));
    for(int i = 0, j = 1; i < N; ++i, j = (j+1)%N){
      int x1 = p[i].first / 2, y1 = p[i].second / 2,
      x2 = p[j].first / 2, y2 = p[j].second / 2;
      if (x1 == x2 || y1 == y2) {
        for (int jj = fmin(y1, y2); jj < fmax(y1, y2); jj++){
          if (x1 > 0)
            wn[x1 - 1][jj] += (y2 > y1 ? -1 : 1);
        }
        continue;
      }
      int cx = x1 + (x2 < x1 ? -1 : 0);
      int cy = y1 + (y2 < y1 ? -1 : 0);
      int dx = (x1 < x2 ? 1 : -1);
      int dy = (y1 < y2 ? 1 : -1);
      bool upd = true;
      while(1){
        fr[cx][cy] = false;
        if (upd) {
          int u = cx;
          int de = idet(2*x1,2*y1,2*x2,2*y2,2*cx+1,2*cy+1) * dy;
          if (de > 0) u--;
          if (u >= 0) wn[u][cy] += -dy;
        }
        if ((cx == (x2 + (x2 < x1 ? 0 : -1))) && (cy == (y2 + (y2 < y1 ? 0 : -1)))) {
          break;
        }
        int d = idet(x1, y1, x2, y2, cx + (x1 < x2 ? 1 : 0), cy + (y1 < y2 ? 1 : 0));
        upd = true;
        if (d == 0){
          cx += dx;
          cy += dy;
        }
        else if ((d < 0 && dx * dy > 0) || (d > 0 && dx * dy < 0))
          cy += dy;
        else { cx += dx; upd = false; }
      }
    }
    int ans = 0;
    for (int x = 199; x >= 0; --x) {
      for (int y = 0; y < 200; ++y) {
        if (x > 0)
          wn[x - 1][y] += wn[x][y];
        if (wn[x][y] == 0)
          continue;
        if (fr[x][y]){
          ans++;
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
