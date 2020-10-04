#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define back(_v) _v.ptr[_v.sz-1]

char* substr(const char* str, size_t begin, size_t len){
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
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
typedef struct{
  char*first;
  char*second;
}pss;
pss newpss(char*a, char*b){
  return(pss){a,b};
}
int cmpP(const void*pa, const void*pb){
  pss*a=(pss*)pa;
  pss*b=(pss*)pb;
  int r1=strcmp(a->first , b->first );
  if(r1!=0)return(r1 < 0)?-1:1;
  int r2=strcmp(a->second, b->second);
  if(r2!=0)return(r2 < 0)?-1:1;
  return 0;
}

/////////////////
int getTime(char*time){
    int h = atoi(substr(time, 0, 2));
    int m = atoi(substr(time, 3, 2));
    return h*60+m;
}
char**alertNames(char**keyName, int keyNameSz, char**keyTime, int keyTimeSz, int*rsz){
    int n = keyNameSz;
    pss nameTime[n];//of pair{ str, str}
    for(int i=0; i<n; ++i){
        nameTime[i] = (pss){keyName[i], keyTime[i]};
    }
    qsort(nameTime, n, sizeof(pss), cmpP);
    vecs names=newVecS();
    for(int i=0; i+2<n; ++i){
        if(strcmp(nameTime[i].first, nameTime[i+2].first)!=0)
            continue;
        int startTime = getTime(nameTime[i].second);
        int endTime   = getTime(nameTime[i+2].second);
        if(endTime-startTime <= 60 && (names.sz==0 || strcmp(nameTime[i].first, back(names))!=0))
           pbs(names, nameTime[i].first);
    }
   *rsz=   names.sz;
    return names.ptr;
}
