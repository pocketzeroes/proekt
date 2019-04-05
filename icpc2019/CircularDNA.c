#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
enum{vsz=1000001};
int main(){
  int N;
  while(scanf("%d", &N)==1){
    vec v  [vsz]; memset(v,   0, sizeof(v)  );
    int cum[N+1]; memset(cum, 0, sizeof(cum));
    int tot[N+1]; memset(tot, 0, sizeof(tot));
    for(int i = 1; i <= N; i++){
      char ch;
      int  s;
      getchar();
      scanf("%c%d", &ch, &s);
      v[s].ptr = pushback(v[s].ptr, &v[s].sz, (ch == 's') ? i : ~i);
    }
    for(int i=0; i < vsz; i++){
      if(v[i].sz){
        int cur = 0, mn = 0;
        for (int j = 0; j < v[i].sz; j++){
          if(v[i].ptr[j] >= 0)
            cur++;
          else
            cur--;
          mn = min(mn, cur);
        }
        if(cur != 0)
          continue;
        for(int j = 0; j < v[i].sz; j++){
          if(v[i].ptr[j] >= 0)
            cur++;
          else
            cur--;
          if(mn == cur){
            cum[~v[i].ptr[j]]++;
            if (j+1 == v[i].sz){
              cum[0]++;
              cum[v[i].ptr[0]]--;
            }
            else
              cum[v[i].ptr[j+1]]--;
          }
        }
      }
    }
    int cur = 0, mx = 0, mxi = 1;
    for(int i=0; i<N+1; i++){
      tot[i] += cur;
      if(tot[i] > mx){
        mx = tot[i];
        mxi = i;
      }
      cur += cum[i];
    }
    printf("%d %d\n", mxi, mx);
  }
  return 0;
}
