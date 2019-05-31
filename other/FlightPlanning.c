#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
const int inf = 1<<20;


vec adj [10000];
int succ[10000];
int kill1, kill2;

int depth(int v, int par){
  int r = 0;
  succ[v] = v;
  for(int z=0;z<adj[v].sz;z++){int it=adj[v].ptr[z];
    if(it != par && (v != kill1 || it != kill2) && (it != kill1 || v != kill2)){
      int d = depth(it, v) + 1;
      if (d > r){
        r = d;
        succ[v] = it;
      }
    }
  }
  return r;
}
int follow(int v, int steps){
  for (int i = 0; i < steps; ++i)
    v = succ[v];
  return v;
}
int main(){
  int n;
  scanf("%d", &n);
  assert(4 <= n && n <= 2500);
  for (int i = 0; i < n-1; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    assert(1 <= a && a <= n);
    assert(1 <= b && b != a && a <= n);
    adj[a].ptr = pushback(adj[a].ptr, &adj[a].sz, b);
    adj[b].ptr = pushback(adj[b].ptr, &adj[b].sz, a);
  }
  kill1 = kill2 = -1;
  memset(succ, -1, sizeof(succ));
  depth(1, -1);
  for (int i = 1; i <= n; ++i)
    assert(succ[i] != -1);
  int v = follow(1, n);
  int olddiam = depth(v, -1);
  int best = inf, bi, bj, ri, rj;
  for (int i = 1; i <= n; ++i){
    for(int z=0;z<adj[i].sz;z++){int it=adj[i].ptr[z];
      if(it > i){
        kill1  = i;
        kill2  = it;
        int d1 = depth(i  , -1);
        int d2 = depth(it, -1);
        int v1 = follow(i, d1);
        int v2 = follow(it, d2);
        assert(succ[v2] == v2);
        int diam1 = depth(v1, -1);
        int diam2 = depth(v2, -1);
        int res = max(max(diam1, diam2), (diam1+1)/2 + (diam2+1)/2 + 1);
        if (res < best)
          best = res, bi = i, bj = it, ri = follow(v1, diam1/2), rj = follow(v2, diam2/2);
      }
    }
  }
  assert(best < olddiam);
  printf("%d\n%d %d\n%d %d\n", best, bi, bj, ri, rj);
}
