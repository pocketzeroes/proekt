#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int vis[1100], rel[1010][1010], n, ns, rid = 1, iid = 1;
int par[1100];

int aug(int v){
  for (int i = ns; i <= n; ++i){
    if (vis[i] != iid && rel[v][i] == rid){
      vis[i] = iid;
      if (!par[i] || aug(par[i]))
        return par[i] = v, par[v] = i, 1;
    }
  }
  return 0;
}
int main(){
  int t, h[1100];
  char s[10], m[1100][40], f[1100][40];
  memset(vis, 0, sizeof(vis));
  memset(rel, 0, sizeof(rel));
  for(int t=1; scanf("%d", &n) == 1, t--; ++rid){
    int gal = 1, boy = n, match = 0, ht, id;
    for (int i = 0; i < n; ++i){
      scanf("%d%s", &ht, s);
      id = *s == 'F' ? gal++ : boy--;
      scanf("%s%s", m[id], f[id]), h[id] = ht;
    }
    ns = gal;
    memset(par, 0, sizeof(par));
    for (int i = 1; i < gal; ++i)
      for (int j = gal; j <= n; ++j)
        if (abs(h[i]-h[j])<=40 && strcmp(f[i], f[j]) && !strcmp(m[i], m[j])){
          rel[i][j] = rid;
          if (!par[i] && !par[j])
            par[j] = i, par[i] = j, ++match;
        }
    for (int i = 1; i < gal; ++i, ++iid)
      if (!par[i])
        match += aug(i);
    printf("%d\n", n-match);
  }
  return 0;
}
