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


int t;
int assigned[101];
int vis     [101];
vec adj     [101];

int visit(int u){
  if(vis[u]!= t)
     vis[u] = t;
  else
    return 0;
  for(int z=0;z<adj[u].sz;z++){int v=adj[u].ptr[z];
    if(!assigned[v] || visit(assigned[v])){
      assigned[v] = u;
      return 1;
    }
  }
  return 0;
}
int main(){
  int n, k;
  scanf("%d %d", &n, &k);
  int a[n+1][n+1]; clr(a);
  int has[n+1]; clr(has);
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      scanf("%d", &a[i][j]);
      has[a[i][j]] = 1;
    }
  }
  for(int d=1; d<=n; d++){
    if(has[d])
      continue;
    for(int i=1; i<=n; i++){
      assigned[i] = vis[i] = 0;
      adj[i].sz=0;
    }
    t = 0;
    for(int i=1; i<=n; i++){
      for(int j=1; j<=n; j++){
        if(!a[i][j])
          pb(adj[i], j);
      }
    }
    for(int i=1; i<=n; i++){
      t++;
      visit(i);
    }
    for(int i=1; i<=n; i++)
      a[assigned[i]][i] = d;
  }
  puts("YES");
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
      printf("%d ", a[i][j]);
    }
    puts("");
  }
  return 0;
}
