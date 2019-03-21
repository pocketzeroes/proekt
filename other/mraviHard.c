#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long double ld;
ld max(ld a, ld b){return a>b?a:b;}

typedef struct edge{
  int v, x, t;
}Edge;

Edge newEdge(int a, int b, int c){
  Edge rez;
  rez.v = a;
  rez.x = b;
  rez.t = c;
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Edge*pushbackE(Edge*array, int *size, Edge value){
  Edge*output = resizeArray(array, Edge, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Edge*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

enum{ MAXN = 1003};
int n;
vece tree[MAXN];
ld needed[MAXN];

bool flow(int u, ld amt, int par){
  if(needed[u] > 0.0 && amt < needed[u])
    return false;
  for(int z=0;z<tree[u].sz;z++){Edge e = tree[u].ptr[z];
    if(e.v == par)
      continue;
    ld goop = amt * e.x / 100.0;
    if (e.t)
      goop = max(goop, goop * goop);
    if(!flow(e.v, goop, u))
      return false;
  }
  return true;
}
int main(){
  scanf("%d", &n);
  int u, v, x, t;
  for (int i = 1; i < n; ++i){
    scanf("%d %d %d %d", &u, &v, &x, &t);
    tree[u].ptr = pushbackE(tree[u].ptr, &tree[u].sz, newEdge(v, x, t));
    tree[v].ptr = pushbackE(tree[v].ptr, &tree[v].sz, newEdge(u, x, t));
  }
  for (int i = 1; i <= n; ++i){
    scanf("%Lf", needed + i);
  }
  ld lo = 0.0L;
  ld hi = 1e15;
  for (int iter = 0; iter < 200; ++iter){
    ld mid = (lo + hi) / 2.0L;
    if(flow(1, mid, -1))
      hi = mid;
    else
      lo = mid;
  }
  printf("%.17Lf\n", hi);
  return 0;
}
