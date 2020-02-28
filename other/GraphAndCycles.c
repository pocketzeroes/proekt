#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void*b, const void*a){//rev
  return ( *(int*)a - *(int*)b );
}
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int*array, int*size, int value){
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
enum{ maxn = 1000};

vec g[maxn + 1];

int main(){
  int n;
  scanf("%d", &n);
  for(int i=1; i<=n*(n-1)/2; i++){
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    pb(g[u], w);
    pb(g[v], w);
  }
  ll ans=0;
  for(int i=1; i<=n; i++){
    qsort(g[i].ptr, g[i].sz, sizeof(int), cmp);// rev
    for(int j=0; j<g[i].sz; j+=2)
      ans += g[i].ptr[j];
  }
  printf("%lld\n", ans);
  return 0;
}
