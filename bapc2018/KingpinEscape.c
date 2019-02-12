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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
///////////////////////
enum{ maxn =(int) 1e5};
vec G[maxn];
vec leaves;

void dfs(int u, int v){
  for(int z=0; z<G[v].sz; z++){int w = G[v].ptr[z];
    if(w != u)
      dfs(v, w);
  }
  if(G[v].sz == 1)
    leaves.ptr = pushback(leaves.ptr, &leaves.sz, v);
}
int main(int taskK, char**BAPC){
  int n, p;
  scanf("%d %d", &n, &p);
  for(int i =0; i!=n-1; ++i){
    int x, y;
    scanf("%d %d", &x, &y);
    G[x].ptr=pushback(G[x].ptr, &G[x].sz, y);
    G[y].ptr=pushback(G[y].ptr, &G[y].sz, x);
  }
  dfs(-1, 0);
  int m = leaves.sz, r = (m+1)/2;
  printf("%d\n", r);
  for(int i=0; i!=r; ++i)
    printf("%d %d\n", leaves.ptr[i], leaves.ptr[i+m/2]);
  return 0;
}
