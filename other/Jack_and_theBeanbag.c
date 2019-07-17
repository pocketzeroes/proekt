#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<stdint.h>
int max(int a,int b){return a>b?a:b;}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int beans;
int need  [ 40];
vec trader[240];
int n;

int32_t check(int64_t mask){
  for(int i=n; i--;){
    bool ok=false;
    for(int z=0;z<trader[i].sz;z++){int j = trader[i].ptr[z];
      if(mask&(1<<j))
        ok=true;
    }
    if(!ok)
      return -1;
  }
  uint32_t res=0;
  for(int i=beans;i--;)
    if(!(mask&(1llu<<(int64_t)i)))
      res+=need[i];
  return res;
}
int main(){
  scanf("%d", &beans);
  for(int i=0; i<beans; i++)
    scanf("%d", &need[i]);
  scanf("%d", &n);
  for(int i=0; i<n; i++){
    int s;
    scanf("%d", &s);
    while(s--){
      trader[i].ptr = pushback(trader[i].ptr, &trader[i].sz, 0);
      scanf("%d", &trader[i].ptr[trader[i].sz-1]);
      --trader[i].ptr[trader[i].sz-1];
    }
  }
  int32_t res=0;
  for(int64_t i=(1llu<<(int64_t)beans); i--;){
    res = max(res, check(i));
  }
  printf("%d\n", res);
  return 0;
}
