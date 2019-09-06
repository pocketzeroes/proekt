#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXR = 4, MAXC = 4};
int R, C, ans = 0;
bool G[MAXR + 2][MAXC + 2];
bool V[MAXR + 2][MAXC + 2];

int dfs1(int r, int c){
  if (r < 1 || r > R || c < 1 || c > C || !G[r][c] || V[r][c]) {
    return 0;
  }
  V[r][c] = true;
  return 1 + dfs1(r - 1, c) + dfs1(r + 1, c) + dfs1(r, c - 1) + dfs1(r, c + 1);
}
int dfs0(int r, int c) {
  if (r < 0 || r > R + 1 || c < 0 || c > C + 1 || G[r][c] || V[r][c]) {
    return 0;
  }
  V[r][c] = true;
  return 1 + dfs0(r - 1, c - 1) + dfs0(r - 1, c + 1) + dfs0(r + 1, c - 1) +
             dfs0(r + 1, c + 1) + dfs0(r - 1, c) + dfs0(r + 1, c) +
             dfs0(r, c - 1) + dfs0(r, c + 1);
}
int main() {
  scanf("%d %d", &R, &C);
  for (int mask = 1; mask < (1 << (R*C)); mask++){
    int r1 = -1, c1 = -1;
    int r0 = -1, c0 = -1;
    memset(G, false, sizeof G);
    for (int i = 0; i < R; i++){
      for (int j = 0; j < C; j++){
        bool bit = (mask >> (i*C + j)) & 1;
        G[i + 1][j + 1] = bit;
        if (bit && r1 == -1){
          r1 = i + 1;
          c1 = j + 1;
        }
        else if (!bit && r0 == -1){
          r0 = i + 1;
          c0 = j + 1;
        }
      }
    }
    int cnt1 = __builtin_popcount(mask);
    int cnt0 = (R + 2)*(C + 2) - cnt1;
    memset(V, false, sizeof V);
    if (cnt1 != dfs1(r1, c1))
      continue;
    memset(V, false, sizeof V);
    if (r0 != -1 && cnt0 != dfs0(r0, c0))
      continue;
    ans++;
  }
  printf("%d\n", ans);
  return 0;
}
