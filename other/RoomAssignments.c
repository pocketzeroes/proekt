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
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
//////////////////////////////

int N,V,E;
vec*c;
int*u;

void go(int n, int mark){
  if(u[n])
    return;
  u[n]=mark;
  V++;
  for(int i=0; i<c[n].sz; i++){
    go(c[n].ptr[i], mark);
    E++;
  }    
}
int main(){
  int runs;
  scanf("%d", &runs);
  while(runs--){
    scanf("%d", &N);
    if(c)free(c);
    c = calloc(N, sizeof(vec));
    for(int i=0; i<N-1; i++){
      int a,b;
      scanf("%d%d", &a, &b);
      a--, b--;
      pb(c[a], b);
      pb(c[b], a);
    }
    int v[N];
    for(int i=0; i<N; i++)
      scanf("%d", &v[i]);
    if(u)free(u);
    u=calloc(N,sizeof(int));
    int ncc=0, ntree=0, tree=-1;
    for(int i=0; i<N; i++){
      if(!u[i]){
        E=V=0;
        go(i,++ncc);
        if(E/2==V-1)
          ntree++, tree=ncc;
      }
    }
    if(ntree>1){
      puts("impossible");
      continue;
    }
    vecp vv=newVecP();
    for(int i=0; i<N; i++)
      if(u[i]==tree)
        vv.ptr = pushbackP(vv.ptr, &vv.sz, newPair(-v[i],i));
    qsort(vv.ptr, vv.sz, sizeof(pair), cmpP);
    int a = vv.ptr[0].second;
    int b = vv.sz>1 ? vv.ptr[1].second : -1;
    bool samev = vv.sz>1 && vv.ptr[0].first==vv.ptr[1].first;
    for(int i=0; i<N; i++){
      if(u[i]!=tree && (!samev || i<b)){
        b=i;
        break;
      }
    }
    if(a>b)
      swap(a, b);
    printf("%d %d\n", a+1, b+1);
  }
  return 0;
}
