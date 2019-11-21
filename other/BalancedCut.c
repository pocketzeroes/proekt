#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)

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
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
////////////////////////////////////

int*p;
int*l;
int*r;
vec*forced;
bool*take;
vec added;
int k, s;
int maxd =(int) 1e9;
int visits;

bool visit(int u){
  ++visits;
  if(take[u])
    return true;
  if(s==k)
    return false;
  for(int z=0;z<forced[u].sz;z++){int v = forced[u].ptr[z];
    if(!visit(v))
      return false;
  }
  if(s==k)
    return false;
  take[u] = true;
  pb(added, u);
  ++s;
  return true;
}
void dfs(int u, int d){
  if(s == k)
    return;
  if(d > maxd)
    return;
  added.sz=0;
  if(! visit(u)){
    s -= added.sz;
    for(int z=0;z<added.sz;z++){int x = added.ptr[z];
      take[x] = false;
    }
    maxd = d-1;
    return;
  }
  if(l[u] != -1)
    dfs(l[u], d+1);
  if(r[u] != -1)
    dfs(r[u], d+1);
}
int main(){
  int n;
  scanf("%d %d", &n, &k);
  p = calloc(n, sizeof(int)); fill(p, n, -1);
  l = calloc(n, sizeof(int)); fill(l, n, -1);
  r = calloc(n, sizeof(int)); fill(r, n, -1);
  int root;
  for(int i=0; i<n; ++i){
    int f;
    scanf("%d", &f);
    --f;
    if(f==-2){
      f = -1;
      root = i;
      continue;
    }
    p[i] = f;
    if(i > f)
      r[f] = i;
    else
      l[f] = i;
  }
  int max_depth = 3+1.5*log(n+2)/log(2);
  int first[n][max_depth]; dfill(first, n, max_depth, -1);
  for(int i = 0; i < n; ++i){
    first[i][0] = i;
    int d = 1;
    int u = p[i];
    while(u != -1){
      if(first[u][d] == -1)
        first[u][d] = i;
      ++d;
      u = p[u];
    }
  }
  forced=calloc(n, sizeof(vec));
  for(int i = 0; i < n; ++i){
    if(p[i] == -1)
      continue;
    int d = 1;
    int u = p[i];
    if(u != -1)
      pb(forced[i], u);
    while(u != -1){
      if(d > 1){
        int f = first[r[u]][d-2];
        if(f != -1)
          pb(forced[i], f);
      }
      u = p[u];
      ++d;
    }
  }
  take = calloc(n, sizeof(bool));
  s = 0;
  dfs(root, 0);
  for(int i = 0; i < n; ++i)
    printf("%d", take[i]);
  puts("");
  return 0;
}
