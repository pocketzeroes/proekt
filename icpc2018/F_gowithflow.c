#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#if 1
int max(int a,int b){return a>b?a:b;}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value){
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
#endif

char buff[100000];
int main(){
  int N;
  while(scanf("%d", &N)==1){
    int mn = 0;
    vec v = newVec();
    for(int i=0; i<N; i++){
      scanf("%s", &buff);
      v.ptr = pushback(v.ptr, &v.sz, strlen(buff));
      mn = max(mn, v.ptr[v.sz-1]);
    }
    int ret = 0, retw = -1;
    for(int w = mn; ; w++){
      int cur [w]; memset(cur , 0, sizeof(cur ));
      int next[w]; memset(next, 0, sizeof(next));
      int cs    = -1,
          nline =  1;
      for(int vi = 0; vi < v.sz; vi++){
        if(cs+v.ptr[vi] >= w){
          memcpy(&cur, &next, sizeof(cur));
          memset(next, 0, sizeof(next));
          cs = -1;
          nline++;
        }
        if(cs >= 0){
          next[cs] = max(cur[cs-1]+1, max(cur[cs]+1, cur[cs+1]+1));
          if(next[cs] > ret){
            ret = next[cs];
            retw = w;
          }
        }
        cs += v.ptr[vi]+1;
      }
      if(ret >= nline)
        break;
    }
    printf("%d %d\n", retw, ret);
  }
  return 0;
}
