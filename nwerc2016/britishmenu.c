#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
///////////////////////////////-------------------------------------------------
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value){
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
///////////////////////////////-------------------------------------------------

const int oo = 1<<30;
vec adj   [1<<20];
int scc_id[1<<20], scc_idx[1<<20], scc_sz[1<<20];
int opt   [1<<20][1<<6];
int depth [1<<20], par[1<<20];

int Opt(int u, int seen){
  seen |= 1 << scc_idx[u];
#define ret opt[u][seen]
  if (!ret) {
    for(int z=0;z<adj[u].sz;z++){int v = adj[u].ptr[z];
      if (scc_id[v] != scc_id[u])
        ret = max(ret, Opt(v,0));
      else if (!(seen & 1 << scc_idx[v]))
        ret = max(ret, Opt(v, seen));
    }
    ++ret;
  }
  return ret;
#undef ret
}
int dfs(int u, int d){
  depth[u] = d;
  int ans = u;
  for(int z=0;z<adj[u].sz;z++){int v = adj[u].ptr[z];
    if (!depth[v])
      v = dfs(v, d+1);
    else
      while (depth[v] == oo && v != par[v])
        v = par[v];
    if (depth[v] < depth[ans])
      ans = v;
  }
  depth[u] = oo;
  return par[u] = ans;
}
int main(void){
  int n, m, ans = 0;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i){
    int a, b;
    scanf("%d %d", &a, &b);
    adj[a].ptr = pushback(adj[a].ptr, &adj[a].sz, b);
  }
  for(int i = 1; i <= n; ++i){
    if(!depth[i])
      dfs(i, 1);
    int r = i;
    while(par[r] != r)
      r = par[r];
    scc_id [i] = r;
    scc_idx[i] = scc_sz[r]++;
  }
  for(int i = 1; i <= n; ++i)
    ans = max(ans, Opt(i,0));
  printf("%d\n", ans);
}




















































