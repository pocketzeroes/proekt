#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define copyVec(best, vis) do{             \
  if(best.ptr)free(best.ptr);              \
  best.sz = vis.sz;                        \
  best.ptr = calloc(vis.sz, sizeof(int));  \
  for(int i=0; i<vis.sz; i++)              \
      best.ptr[i] = vis.ptr[i];            \
}while(0)
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
/////////////////////////////////

vec reduct(vec pv, vec*p){
  vec v=newVec(); copyVec(v, pv);
  for(int i = 0; i < p->sz; ++i)
    if(!v.ptr[p->ptr[i]]--)
      return newVec();
  return v;
}
int gen(vec pv, vec plb, int tobeat){
  vec v  = newVec(); copyVec(v, pv);
  vec lb = newVec(); copyVec(lb, plb);
  int tot = 0;
  for(int i=0; i<v.sz; ++i)
    tot += v.ptr[i];
  if(lb.sz==0)
    pb(lb, 0);
  else{
    for(int i=0; ++lb.ptr[i] >= v.sz; ++i){
      if(i == lb.sz-1){
        pb(lb, 0);
        memset(lb.ptr, 0, lb.sz*sizeof(int));
        break;
      }
      else{
        lb.ptr[i] = lb.ptr[i+1]+1;
        for(int j=0; j<i; ++j)
          lb.ptr[j] = lb.ptr[i];
      }
    }
  }
  if(tobeat >= tot/lb.sz)
    return tobeat;
  vec g = reduct(v, &lb);
  if(g.sz>0)
    tobeat = 1+gen(g, lb, fmax(tobeat-1, 0));
  tobeat = gen(v, lb, tobeat);
  return tobeat;
}
int main(){
  ll X;
  vec v=newVec();
  scanf("%lld", &X);
  int k=0;
  for(ll p=2; p*p <= X; ++p){
    int e=0;
    while(X%p == 0)
      X /= p, ++e;
    if(e){
      ++k;
      if(e > 1)
        pb(v, e-1);
    }
  }
  if(X != 1)
    ++k;
  vec lb = newVec();
  pb(lb, v.sz);
  if(v.sz>0)
    k += gen(v, lb, 0);
  printf("%d\n", k);
  return 0;
}
