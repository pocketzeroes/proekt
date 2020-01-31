#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
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
#define pbl(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
/////////////////////////////////

enum{ maxn = 100005};
enum{ maxf = 105   };
int dp[maxn][maxf];
vec heights[maxn];
vecl fib;
vec G[maxn];

void GenerateFib(){
  ll f1 = 1;
  ll f2 = 1;
  pbl(fib, f1);
  pbl(fib, f2);
  for(int i=3; i<maxf; i++){
    ll f3 = f1 + f2;
    f1 = f2;
    f2 = f3;
    pbl(fib, f3);
  }
}
int DFS(int u, int h){
#define ret dp[u][h]
  if(ret != -1)
    return ret;
  ret = 0;
  for(int z=0;z<G[u].sz;z++){int v = G[u].ptr[z];
    for(int q=0; q<heights[v].sz; q++){int height = heights[v].ptr[q];
      if(height - 1 == h){
        int candidate = 1 + DFS(v, height);
        ret = fmax(ret, candidate);
      }
    }
  }
  return ret;
  #undef ret
}
int main(){
  GenerateFib();
  int n, m;
  scanf("%d %d", &n, &m);
  for(int i=1; i<=n; i++){
    ll h;
    scanf("%lld", &h);
    for(int j=0; j<fib.sz; j++){
      if(fib.ptr[j] == h)
        pb(heights[i], j);
    }
  }
  while(m--){
    int x, y;
    scanf("%d %d", &x, &y);
    pb(G[x], y);
    pb(G[y], x);
  }
  memset(dp, -1, sizeof dp);
  int ans=0;
  for(int i=1; i<=n; i++){
    for(int z=0;z<heights[i].sz;z++){int height = heights[i].ptr[z];
      int candidate = 1 + DFS(i, height);
      ans = fmax(ans, candidate);
    }
  }
  printf("%d\n", ans);
  return 0;
}
