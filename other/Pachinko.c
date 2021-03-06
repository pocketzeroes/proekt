#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int W, H, Pu, Pd, Pl, Pr;
char*g[10000];
bool seen[10000][20];
double M[10000][20][61], V[10000][20];

void dfs(int x, int y) {
  if (x < 0 || x >= W || y < 0 || y >= H || g[y][x] == 'X') return;
  if (seen[y][x]) return;
  seen[y][x] = true;
  if (g[y][x] == 'T') return;
  dfs(x-1, y);
  dfs(x+1, y);
  dfs(x, y-1);
  dfs(x, y+1);
}
int main(){
  while(scanf("%d %d", &W, &H)==2){
    scanf("%d%d%d%d", &Pu, &Pd, &Pl, &Pr);
    for(int y = 0; y < H; y++)
      g[y] = getstr();
    memset(seen, 0, sizeof(seen));
    memset(M, 0, sizeof(M));
    memset(V, 0, sizeof(V));
    int ns = 0;
    for (int x = 0; x < W; x++) if (g[0][x] == '.') {ns++; dfs(x, 0);}
    for (int x = 0; x < W; x++) if (g[0][x] == '.') M[0][x][60] = 1.0 / ns;
    for (int y = 0; y < H; y++)
    for (int x = 0; x < W; x++) {
      M[y][x][20+x] = 1.0;
      if (g[y][x] != '.' || !seen[y][x]) continue;
      double P = 0;
      if (x > 0   && g[y][x-1] != 'X') P += Pl;
      if (x < W-1 && g[y][x+1] != 'X') P += Pr;
      if (y > 0   && g[y-1][x] != 'X') P += Pu;
      if (y < H-1 && g[y+1][x] != 'X') P += Pd;
      if (P == 0) continue;
      if (x > 0   && g[y][x-1] != 'X') M[y][x-1][20+x] -= Pl / P;
      if (x < W-1 && g[y][x+1] != 'X') M[y][x+1][20+x] -= Pr / P;
      if (y > 0   && g[y-1][x] != 'X') M[y-1][x][40+x] -= Pu / P;
      if (y < H-1 && g[y+1][x] != 'X') M[y+1][x][   x] -= Pd / P;
    }
    for (int y = 0; y < H; y++)
    for (int x = 0; x < W; x++) if (seen[y][x]) {
      double c = M[y][x][20+x];
      for (int i = 20+x; i < 61; i++) M[y][x][i] /= c;
      for (int x2 = x+1; x2 < W; x2++) {
        c = M[y][x2][20+x];
        for (int i = 20+x; i < 61; i++) M[y][x2][i] -= c * M[y][x][i];
      }
      if (y < H-1) for (int x2 = 0; x2 < W; x2++) {
        c = M[y+1][x2][x];
        for (int i = 20+x; i < 60; i++) M[y+1][x2][i-20] -= c * M[y][x][i];
        M[y+1][x2][60] -= c * M[y][x][60];
      }
    }
    double tot = 0.0;
    for (int y = H-1; y >= 0; y--)
    for (int x = W-1; x >= 0; x--) if (seen[y][x]) {
#define v V[y][x]
      v = M[y][x][60];
      for (int i = 20+x+1; i < 40; i++) v -= M[y][x][i] * V[y][i-20];
      if (y < H-1) for (int i = 40; i < 60; i++) v -= M[y][x][i] * V[y+1][i-40];
      tot += v;
    }
    #undef v
    assert(tot < 1e9);
    for (int y = 0; y < H; y++)
    for (int x = 0; x < W; x++) if (g[y][x] == 'T') {
      printf("%.9lf\n", V[y][x]);
    }
  }
  return 0;
}
