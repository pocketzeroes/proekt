#pragma GCC optimize "-O3"
#include <stdio.h>
#include <string.h>

#define MAXN 100000
#define INF  1000000000

int ut[MAXN], nxt[2 * MAXN], nd[2 * MAXN], da;
char tp[MAXN];
int prev[MAXN];
int v[MAXN], dv, p[MAXN];
int d[MAXN];

inline void add(int a, int b){
  nd[da] = b;
  nxt[da] = ut[a];
  ut[a] = da;
  da++;
}
void dfs(int x, int t){
  int poz;
  poz = ut[x];
  while(poz != -1){
    if(nd[poz] != t){
      d[nd[poz]] = d[x] + 1;
      prev[nd[poz]] = x;
      dfs(nd[poz], x);
    }
    poz = nxt[poz];
  }
}
inline int caut(int n){
   int i, mx = -1, p;
   for(i = 0; i < n; i++){
     if(d[i] > mx){
       mx = d[i];
       p = i;
     }
   }
   return p;
}
int cobor(int x, int t){
  int poz = ut[x], mx = 0, k;
  while(poz != -1){
    if(tp[nd[poz]] == 0 && nd[poz] != t){
      k = cobor(nd[poz], x);
      if(mx < k)
        mx = k;
    }
    poz = nxt[poz];
  }
  return mx + 1;
}
int main(){
  int n, i, a, b, x;
  scanf("%d", &n);
  memset(ut, -1 , sizeof ut);
  for(i = 0; i < n - 1; i++){
    scanf("%d%d", &a, &b);
    a--;  b--;
    add(a, b);
    add(b, a);
  }
  prev[0] = -1;
  d[0] = 0;
  dfs(0, -1);
  x = caut(n);
  prev[x] = -1;
  d[x] = 0;
  dfs(x, -1);
  x = caut(n);
  int cx = x;
  while(prev[cx] != -1){
    v[dv++] = cx;
    tp[cx] = 1;
    cx = prev[cx];
  }
  v[dv++] = cx;
  tp[cx] = 1;
  cx = x;
  int poz = 0, cr = INF, r = 0;
  for(i = 0; i < dv; i++){
    p[i] = cobor(v[i], -1) - 1;
    if(p[i] > 0 && poz - p[i] < cr)
      cr = poz - p[i];
    poz++;
  }
  r += cr;
  poz = 0;
  cr = INF;
  for(i = dv - 1; i >= 0; i--){
    if(p[i] > 0 && poz - p[i] < cr)
      cr = poz - p[i];
    poz++;
  }
  r += cr;
  if(r >= n)
    r = n - 1;
  printf("%d", r);
  return 0;
}













