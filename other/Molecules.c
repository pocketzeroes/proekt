#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<complex.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define newpt __builtin_complex
typedef complex double pt;

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

/////////////////////////////////////////
enum{ MAXN       = 100  };
enum{ ITERATIONS = 50000};


int main(){
  int n, m;
  vec g[MAXN]; clr(g);
  pt pts[MAXN], tmp[MAXN];
  bool anchored[MAXN];
  scanf("%d %d", &n, &m);
  for(int u=0; u<n; ++u){
    int x, y;
    scanf("%d %d", &x, &y);
    anchored[u] = (x != -1 || y != -1);
    pts[u] = newpt((double)x, (double)y);
  }
  while(m--){
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;
    pb(g[u], v);
    pb(g[v], u);
  }
  for(int iter=0; iter<ITERATIONS; ++iter){
    for(int u=0; u<n; ++u){
      if(anchored[u])
        tmp[u] = pts[u];
      else{
        pt delta=newpt(0.0, 0.0);
        for(int z=0; z<g[u].sz; z++){int v = g[u].ptr[z];
          delta += pts[v];
        }
        tmp[u] = 0.5*pts[u] + 0.5*delta/(double)(g[u].sz);
      }
    }
    for(int u=0; u<n; ++u)
      pts[u] = tmp[u];
  }
  for(int u=0; u<n; ++u)
    printf("%.10lf %.10lf\n", creal(pts[u]), cimag(pts[u]));
  return 0;
}
