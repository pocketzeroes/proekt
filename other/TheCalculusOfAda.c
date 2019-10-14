#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
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
////////////////////////
vec seq;
vec lasts;

bool done(){
  if(seq.sz == 1)
     return true;
  bool change = false;
  int orig = seq.ptr[0];
  for(int k=1; k < seq.sz; k++)
    if(orig != seq.ptr[k])
       return false;
  return true;
}
int main(){
  int n,v;
  scanf("%d", &n);
  for(int j=0; j<n; j++){
    scanf("%d", &v);
    pb(seq, v);
  }
  pb(lasts, seq.ptr[seq.sz-1]);
  int d=0;
  while(!done()){
    d++;
    for(int k=0; k < seq.sz-1; k++)
      seq.ptr[k] = (seq.ptr[k+1] - seq.ptr[k]);
    seq.sz--;
    pb(lasts, seq.ptr[seq.sz-1]);
  }
  int total = 0;
  for(int z=0;z<lasts.sz;z++){int v = lasts.ptr[z];
    total += v;
  }
  printf("%d %d\n", d, total);
  return 0;
}
