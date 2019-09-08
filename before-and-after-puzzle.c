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
  return ptr;
}
char*concats(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", a, b);
  return ptr;
}
int unique(char**a, int len){
	int i, j;
	for(i = j = 0; i < len; i++)
		if(strcmp(a[i], a[j])!=0)
      a[++j] = a[i];
	return j + 1;
}

#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
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
vecs split(char*s){
  vecs rez=newVecS();
  char n[100];
  while(1){
    sscanf(s, "%s", &n);
    rez.ptr = pushbackS(rez.ptr, &rez.sz, strdup(n));
    s = strchr(s, ' ');
    if(s==NULL)break;
    s++;
  }
  return rez;
}
///////////////////////////////////////
char**beforeAndAfterPuzzles(char**P, int Psz, int*rsz){
  vecs ret=newVecS();
  for(int i = 0; i < Psz; i++){
    for(int j = 0; j < Psz; j++){
      if(i!=j){
        vecs a = split(P[i]);
        vecs b = split(P[j]);
        if(a.sz == 0 || b.sz == 0)
          continue;
        if(strcmp(a.ptr[a.sz-1], b.ptr[0])==0){
          char*r = strdup(P[i]);
          char*r2= strdup(P[j]);
          r2+=strlen(a.ptr[a.sz-1]);
          r = concats(r, r2);
          ret.ptr = pushbackS(ret.ptr, &ret.sz, r);
        }
      }
    }
  }
  if(ret.sz>0){
    qsort(ret.ptr, ret.sz, sizeof(char*), cmpstr);
    ret.sz = unique(ret.ptr, ret.sz);
   *rsz=   ret.sz;
    return ret.ptr;
  }
  ret.ptr=pushbackS(ret.ptr, &ret.sz, strdup(""));
  *rsz=0;
  return ret.ptr;
}
// int main(){   return 0; }
