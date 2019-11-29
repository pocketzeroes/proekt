#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
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
/////////////////////
enum{ N=200};
enum{ K=22 };
int w[N][N];
int seen[N];
int dp[1<<K];

int get(vec*v, int k, int mask){
  int*x = &dp[mask];
  if(*x != -1)
    return*x;
  if(k == v->sz){
    *x=0;
    return 0;
  }
  if(mask&(1<<k))
    return get(v, k+1, mask);
  else{
    *x=1000000000;
    mask|=(1<<k);
    for(int i=0; i<v->sz; ++i){
      if(mask&(1<<i))
        continue;
      *x = fmin(*x, w[v->ptr[i]][v->ptr[k]] + get(v, k+1, mask|(1<<i)));
    }
  }
  return *x;
}
int match(vec*v){
  memset(dp, -1, sizeof(dp));
  return get(v, 0, 0);
}
int main(){
  int n, m;
  scanf("%d %d", &n, &m);
  vec g[n]; clr(g);
  for(int i=0; i<n; ++i)
    pb(g[i], i);
  for(int i=0; i<m; ++i){
    int a, b, ww;
    scanf("%d %d %d", &a, &b, &ww);
    a--, b--;
    pb(g[a], b);
    pb(g[b], a);
    w[a][b] = w[b][a] = ww;
  }
  clr(seen);
  int ans=0;
  for(int i=0; i<n; ++i){
    if(g[i].sz&1){
      puts("impossible");
      return 0;
    }
    if(seen[i])
      continue;
    for(int z=0;z<g[i].sz;z++){int v = g[i].ptr[z];
      seen[v] = true;
    }
    ans += match(&g[i]);
  }
  printf("%d\n", ans);
  return 0;
}
