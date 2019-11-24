#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmpstr(const void*p1, const void*p2){
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  free(a);
  return ptr;
}
int lower_bound(char**a, int n, char*x){
  int l = 0;
  int h = n;
  while (l < h) {
    int mid = (l + h) / 2;
    if(strcmp(x, a[mid])<=0)
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}
#define pbs(zpv, zvv) zpv.ptr = pushbackS(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
char**pushbackS(char**array, int *size, char*value) {
  char**output = resizeArray(array, char*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  char**ptr;
  int sz;
}vecs;
vecs newVecS(){
  vecs rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}


char***suggestedProducts(char**ps, int psSz, char*S, int*rsz, int**csz){
    qsort(ps, psSz, sizeof(char*), cmpstr);
    int retsz = strlen(S);
    int*cols = calloc(retsz, sizeof(int));
    char***ret = calloc(retsz, sizeof(char**));
    char*q = strdup("");
    for(int z=0; z<retsz; z++){char c = S[z];
        q = concatc(q, c);
        int i = lower_bound(ps, psSz, q);
        vecs app = newVecS();
        for(int j=i,j_end_=i+3; j<j_end_; j++){
            if(j<psSz){
                if(strncmp(q, ps[j], strlen(q))==0)
                    pbs(app, ps[j]);
            }
        }
        cols[z]= app.sz;
        ret[z] = app.ptr;
    }
   *csz = cols;
   *rsz =  retsz;
    return ret;
}
//int main(){
//    return 0;
//}
