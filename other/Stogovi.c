#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
enum{ MAXN = 300100};
enum{ LG   = 20    };
int L[MAXN][LG];
int d[MAXN];
int x[MAXN];


int lca(int u, int v){
  if (d[u] < d[v])
    swap(u, v);
  for (int j = LG-1; j >= 0; --j)
    if (d[u]-(1<<j) >= d[v]) u = L[u][j];
  if (u == v)
    return u;
  for (int j = LG-1; j >= 0; --j)
    if (L[u][j] != L[v][j])
      u = L[u][j], v = L[v][j];
  return L[u][0];
}
int main(){
  int n;
  scanf("%d", &n);
  L[0][0] = -1, d[0] = 0, x[0] = 0;
  for (int i = (1); i < (n+1); ++i) {
    char s[10];
    int v;
    scanf("%s %d", s, &v);
    v = x[v];
    if (s[0] == 'a') {
      x[i] = i;
      d[i] = d[v] + 1;
      L[i][0] = v;
      for (int j = (1); j < (LG); ++j)
        if (L[i][j-1] != -1) L[i][j] = L[ L[i][j-1] ][j-1]; else
          L[i][j] = L[i][j];
    }
    if (s[0] == 'b') {
      assert(v > 0);
      printf("%d\n", v);
      x[i] = L[v][0];
    }
    if (s[0] == 'c') {
      int w;
      scanf("%d", &w);
      w = x[w];
      x[i] = v;
      printf("%d\n", d[lca(v, w)]);
    }
  }
  return 0;
}
