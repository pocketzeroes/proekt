#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
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
typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
enum{ ms =(int) 3e5+2};/////////////////////////////////////////////

vec  g       [ms];
pair rota    [ms];
int  vis     [ms];
int  mark    [ms];
int  routMark[ms];
vec  start   [ms],
     finish  [ms];
vec  topo;

void dfs(int u){
  if(vis[u])
    return;
  vis[u] = 1;
  for(int z=0;z<g[u].sz;z++){int v = g[u].ptr[z];
    dfs(v);
  }
  topo.ptr = pushback(topo.ptr, &topo.sz, u);
}
void dfsMark(int u){
  if(mark[u])
    return;
  mark[u] = 1;
  for(int z=0;z<finish[u].sz;z++){int v = finish[u].ptr[z];
    routMark[v] = 1;
  }
  for(int z=0;z<g[u].sz;z++){int v = g[u].ptr[z];
    dfsMark(v);
  }
}
int main(){
  int n, k, m;
  scanf("%d%d%d", &n, &k, &m);
  for(int i = 0; i < k; i++){
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].ptr = pushback(g[u].ptr, &g[u].sz, v);
  }
  for(int i = 0; i < m; i++){
    int u, v;
    scanf("%d%d", &u, &v);
    rota [i] =(pair){u, v};
    start [u].ptr = pushback(start[u].ptr , &start[u].sz , i);
    finish[v].ptr = pushback(finish[v].ptr, &finish[v].sz, i);
  }
  for(int i = 1; i <= n; i++)
    dfs(i);
  int ans = 0;
  for(int z=0; z<topo.sz; z++){int u = topo.ptr[z];
    bool need = false;
    for(int q=0;q<start[u].sz;q++){int v = start[u].ptr[q];
      if(!routMark[v])
        need = true;
    }
    if(need){
      dfsMark(u);
      ans++;
    }
  }
  printf("%d\n", ans);
  return 0;
}
