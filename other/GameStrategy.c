#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)
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
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}


int main(){
  int N;
  while(scanf("%d", &N)==1){
    vec v[N];clr(v);
    for(int i = 0; i < N; i++){
      int M;
      scanf("%d", &M);
      for(int j=0; j<M; j++){
        char*s=getstr();
        int b = 0;
        for(int k = 0; s[k]; k++)
          b |= (1<<(s[k]-'a'));
        pb(v[i], b);
      }
    }
    int ret[N][N]; dfill(ret, N, N, -1);
    for(int es = 0; es < N; es++){
      int b = (1<<es);
      ret[es][es] = 0;
      for(int steps = 1; ; steps++){
        int b2 = b;
        for (int i = 0; i < N; i++)
          if (!(b&(1<<i))){
            for(int j = 0; j < v[i].sz; j++)
              if ((b & v[i].ptr[j]) == v[i].ptr[j]){
                b2 |= (1<<i);
                ret[i][es] = steps;
                break;
              }
          }
        if (b2 == b)
          break;
        b = b2;
      }
    }
    for (int ss = 0; ss < N; ss++){
      for (int es = 0; es < N; es++){
        printf("%d", ret[ss][es]);
        if (es < N-1)
          printf(" ");
        else
          puts("");
      }
    }
  }
  return 0;
}
