#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int *array, int *size, int value){
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
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
////////////////////
int n;
void dfs(int u, char**b, vec*s, int*vis){
  vis[u] = 1;
  for(int v = 0; v < n; ++v)
    if(b[u][v] == '1' && vis[v] < 0)
      dfs(v, b, s, vis);
  s->ptr = pushback(s->ptr, &s->sz, u);
}
int main(){
  scanf("%d", &n);
  char*b[n];
  for(int i=0;i<n;i++)
    b[i] = getstr();
  vec s = newVec();
  int vis[n];
  fill(vis, n, -1);
  dfs(0, b, &s, vis);
  if(s.sz < n)
    puts("impossible");
  else
    for(int i=0; i<n; ++i)
      printf("%d%c", s.ptr[i], " \n"[i+1 == n]);
  return 0;
}
