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
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
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
int cmpP(const void*pb, const void*pa){//rev
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
////////////////////////////

int*filterRestaurants(int**mat, int matSz, int*mat0sz, int vf, int PM, int DM, int*rsz){
    vecp v = newVecP();
    for(int i=0,i_end_=matSz; i<i_end_; i++){
        if(mat[i][3] <= PM && mat[i][4] <= DM){
          if(vf && !mat[i][2])
            continue;
          pbp(v, newpair(mat[i][1], mat[i][0]));
        }
    }
    if(v.ptr!=NULL&&v.sz>=1)
      qsort(v.ptr, v.sz, sizeof(pair), cmpP);//rev
    vec ret = newVec();
    for(int z=0; z<v.sz; z++){pair p = v.ptr[z];
        pb(ret, p.second);
    }
    *rsz = ret.sz;
    return ret.ptr;
}
// int main(){
//     return 0;
// }
