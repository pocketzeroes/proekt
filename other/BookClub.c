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

enum{ MAXN = 100000};

int n,m;

vec g      [MAXN];
int visited[MAXN];
int pairs  [MAXN];

bool bpm(int v){
  if (visited[v])
    return false;
  visited[v] = true;
  for (size_t i = 0; i<g[v].sz; i++){
    if(pairs[g[v].ptr[i]] == -1 || bpm(pairs[g[v].ptr[i]])){
      pairs [g[v].ptr[i]] = v;
      return true;
    }
  }
  return false;
}
int main(){
  scanf("%d %d", &n, &m);
  int a,b;
  for (int i = 0; i<m; i++){
    scanf("%d %d", &a, &b);
    g[a].ptr = pushback(g[a].ptr, &g[a].sz, b);
  }
  memset(pairs, -1, sizeof(pairs));
  int cnt = 0;
  for (int i = 0; i<n; i++){
    memset(visited, 0, sizeof(visited));
    if (bpm(i))
      cnt++;
  }
  puts((cnt==n?"YES": "NO"));
  return 0;
}
