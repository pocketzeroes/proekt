#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
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

enum{ MAXN = 200005};

vec E   [MAXN],
    RE  [MAXN],
    rdom[MAXN];
int S[MAXN], RS[MAXN], cs;
int par[MAXN], val[MAXN], sdom[MAXN], rp[MAXN], dom[MAXN];

void clear(int n){
  cs = 0;
  for(int i=0;i<=n;i++){
    par[i] = val[i] = sdom[i] = rp[i] = dom[i] = S[i] = RS[i] = 0;
    E   [i].sz=0;
    RE  [i].sz=0;
    rdom[i].sz=0;
  }
}
void add_edge(int x, int y){
  pb(E[x], y);
}
void Union(int x, int y){
  par[x] = y;
}
int Find(int x, int c){
  if(par[x] == x)
    return c ? -1 : x;
  int p = Find(par[x], 1);
  if(p == -1)
    return c ? par[x] : val[x];
  if(sdom[val[x]] > sdom[val[par[x]]])
    val[x] = val[par[x]];
  par[x] = p;
  return c ? p : val[x];
}
void dfs(int x){
  RS[ S[x] = ++cs ] = x;
  par[cs] = sdom[cs] = val[cs] = cs;
  for(int z=0;z<E[x].sz;z++){int e = E[x].ptr[z];
    if(S[e] == 0)
      dfs(e), rp[S[e]] = S[x];
    pb(RE[S[e]], S[x]);
  }
}
int solve(int s, int*up){
  dfs(s);
  for(int i=cs;i;i--){
    for(int z=0;z<RE[i].sz;z++){int e = RE[i].ptr[z];
      sdom[i] = fmin(sdom[i], sdom[Find(e,0)]);
    }
    if(i > 1)
      pb(rdom[sdom[i]], i);
    for(int z=0;z<rdom[i].sz;z++){int e = rdom[i].ptr[z];
      int p = Find(e,0);
      if(sdom[p] == i)
        dom[e] = i;
      else
        dom[e] = p;
    }
    if(i > 1)
      Union(i, rp[i]);
  }
  for(int i=2;i<=cs;i++)
    if(sdom[i] != dom[i])
      dom[i] = dom[dom[i]];
  for(int i=2;i<=cs;i++)
    up[RS[i]] = RS[dom[i]];
  return cs;
}
int chk[MAXN];

int main(){
  int n, m, t;
  scanf("%d %d %d", &n, &m, &t);
  for(int i=0; i<m; i++){
    int s, e;
    scanf("%d %d", &s, &e);
    swap(s, e);
    if(s == t)
      chk[e + 1] = n + i + 1;
    add_edge(s + 1, n + i + 1);
    add_edge(n + i + 1, e + 1);
  }
  int up[MAXN];
  solve(t + 1, up);
  vec ans = newVec();
  for(int i=0; i<n; i++){
    if(chk[i + 1] && up[i + 1] == chk[i + 1]){
      pb(ans, i);
    }
  }
  printf("%d\n", ans.sz);
  for(int z=0;z<ans.sz;z++)
    printf("%d\n", ans.ptr[z]);
  return 0;
}
