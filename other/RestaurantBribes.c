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
typedef struct{
  int    first;
  double second;
}pair;
pair newpair(int a, double b){
  return(pair){a,b};
}
//////////////////

double opt(double a, double b){
  double mx=0;
  for(int x=1;x<=10;++x)
    mx = fmax(mx, b*x-a*a*x*x);
  return mx;
}
int main(){
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  vec g[n]; clr(g);
  for(int i=0;i<m;++i){
    int a, b;
    scanf("%d %d", &a, &b);
    --a, --b;
    pb(g[a], b);
    pb(g[b], a);
  }
  int isbribed[n]; clr(isbribed);
  pair bribes[k];//pair{int, double}
  for(int z=0;z<k;z++){
    scanf("%d %lf", &bribes[z].first, &bribes[z].second);
    bribes[z].first--;
    isbribed[bribes[z].first] = true;
  }
  vec ng[n]; clr(ng);
  for(int i=0;i<n;++i){
    for(int z=0;z<g[i].sz;z++){int v=g[i].ptr[z];
      if(isbribed[v])
        pb(ng[i], v);
    }
  }
  double ans=0;
  for(int z=0;z<k;z++){pair x=bribes[z];
    double influence=0;
    for(int q=0;q<g[x.first].sz;q++){int j=g[x.first].ptr[q];
      if(isbribed[j])
        continue;
      influence+=100./ng[j].sz;
    }
    ans += opt(x.second, influence);
  }
  printf("%.10f\n", ans);
  return 0;
}
