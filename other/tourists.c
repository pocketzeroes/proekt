#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

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

typedef long long ll;

enum{ MAX    =(int)2e5 + 10};
enum{ MAXLOG = 20          };
vec adj[MAX];
int table[MAX][MAXLOG], depth[MAX];


ll gcd(ll first, ll second){
  return !second ? first : gcd(second, first % second);
}
ll lcm(ll first, ll second){
  return (first / gcd(first, second)) * second;
}
void dfs(int u, int p){
  table[u][0] = p;
  for(int i=0; i<adj[u].sz; i++){
    int v = adj[u].ptr[i];
    if(v == p)
      continue;
    depth[v] = depth[u] + 1;
    dfs(v, u);
  }
}
int LCA(int u, int v){
  if(depth[u] < depth[v])
    swap(u, v);
  for(int k = MAXLOG-1; k >= 0; k--)
    if(depth[u] - (1 << k) >= depth[v])
      u = table[u][k];
  if(u == v)
    return u;
  for(int k = MAXLOG-1; k >= 0; k--){
    if(table[u][k] != table[v][k]){
      u = table[u][k];
      v = table[v][k];
    }
  }
  return table[u][0];
}
int length(int u, int v){
  return depth[u] + depth[v] - 2 * depth[LCA(u, v)];
}
int main(){
  int n;
  scanf("%d", &n);
  for(int i=1; i<n; i++){
    int u, v;
    scanf("%d %d", &u, &v);
    u--, v--;
    adj[u].ptr = pushback(adj[u].ptr, &adj[u].sz, v);
    adj[v].ptr = pushback(adj[v].ptr, &adj[v].sz, u);
  }
  memset(table, -1, sizeof table);
  dfs(0, -1);
  for(int k=1; k<MAXLOG; k++){
    for(int u=0; u<n; u++){
      if(table[u][k - 1] == -1)
        continue;
      table[u][k] = table[table[u][k - 1]][k - 1];
    }
  }
  ll res = 0;
  for(int i=1; i<=n; i++)
    for(int j=2*i; j<=n; j+=i)
      res += length(i - 1, j - 1) + 1;
  printf("%lld\n", res);
  return 0;
}
