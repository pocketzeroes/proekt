#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ inf = 1<<25};
int N;
int dist   [410][410];
int shift  [410], avail[410];
int mintime[410];
int LO;

inline double sqr(double x) {
  return x*x;
}
int bellman_ford(int src, int startt){
  int back[500];
  for (int i = 0; i < N; ++i)
    mintime[i] = startt + dist[src][i], back[i] = -1;
  back[src] = src;
  for (int i = 0; i <= N; ++i){
    for (int u = 0; u < N; ++u){
      for (int v = 0; v < N; ++v){
        int nt = mintime[u] + dist[u][v];
        if (u >= 2 && u % 2 == 0 && v == u+1)
          nt = min(nt, max(mintime[u], avail[u]) + shift[u]);
        if (nt < mintime[v]) {
          mintime[v] = nt;
          back[v] = u;
          if (i == N) {
            while (back[u] != -1) 
              v = back[u], back[u] = -1, u = v;
            return u;
          }
        }
      }
    }
  }
  return -1;
}
int besttime(int u){
  int lo = LO-1, hi = mintime[u];
  while (hi - lo > 1){
    int m = (lo+hi)/2+1;
    bellman_ford(u, m);
    if (mintime[u] < m)
      hi = mintime[u];
    else
      lo = m-1;
  }
  return hi;
}
void solve(){
  int n;
  int x[500], 
      y[500], 
      z[500];
  scanf("%d%d%d%d%d%d%d\n", x, y, z, x+1, y+1, z+1, &n);
  N = 2*n+2;
  for (int i = 2; i < N; i += 2) {
    scanf("%d%d%d%d%d%d%d%d", x+i, y+i, z+i, x+i+1, y+i+1, z+i+1, avail+i, shift+i);
    LO = min(LO, avail[i]+shift[i]);
  }
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j) {
      double d = sqrt(sqr(x[i]-x[j]) + sqr(y[i]-y[j]) + sqr(z[i]-z[j]));
      dist[i][j] = (int)(ceil(d)+0.01);
    }
  
  int v = bellman_ford(0, 0);
  while (v != -1) {
    int t = besttime(v);
    v = bellman_ford(v, t);
  }
  printf("%d\n", mintime[1]);
}
int main(){
  int T;
  scanf("%d", &T);
  for (int i = 0; i < T; ++i)
    solve();
  return 0;
}
