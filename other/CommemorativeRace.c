#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

enum{ N =(int) 1e5 + 5};
int vis[N], d[N], d2[N], cnt[N], ans[N];
vec G[N];

int dfs(int x){
  if (vis[x] == 1)
    return d[x];
  vis[x] = 1;
  for(int z=0;z<G[x].sz;z++){int u = G[x].ptr[z];
    int tmp = dfs(u) + 1;
    if (tmp > d[x]) {
      d2[x] = d[x];
      d[x] = tmp;
    }
    else if (tmp > d2[x])
      d2[x] = tmp;
  }
  return d[x];
}
void dfs2(int x, int d_up){
  if (vis[x] == 2)
    return;
  vis[x] = 2;
  for(int z=0;z<G[x].sz;z++){int u = G[x].ptr[z];
    if(d[x] == d[u] + 1){
      dfs2(u, d_up + 1);
      cnt[d_up] ++;
      ans[d_up] = d_up + d2[x];
    }
  }
}
int main(){
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++ i)
    pb(G[0], i);
  for (int i = 0; i < m; ++ i) {
    int u, v;
    scanf("%d %d", &u, &v);
    pb(G[u], v);
  }
  dfs(0);
  dfs2(0,0);
  int res = d[0];
  for (int i = 1; i <= n; ++ i)
    if (cnt[i] == 1)
      res = fmin(res, ans[i]);
  printf("%d\n", res - 1);
  return 0;
}
