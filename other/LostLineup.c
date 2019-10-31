#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pb(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
//////////////////////

int main(){
  vecp v = newVecP();
  int N;
  scanf("%d", &N);
  pb(v, newpair(-1, 1));
  for(int i=0; i<N-1; i++){
    int x;
    scanf("%d", &x);
    pb(v, newpair(x, i+2));
  }
  qsort(v.ptr, v.sz, sizeof(pair), cmpP);
  for(int z=0;z<v.sz;z++){pair p = v.ptr[z];
    printf("%d ", p.second);
  }
  puts("");
  return 0;
}
