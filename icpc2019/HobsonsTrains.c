#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
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

int main() {
  int N, K;
  while(scanf("%d %d", &N, &K)==2){
    int succ[N]; memset(succ, 0, sizeof(succ));
    int ret[N]; fill(ret, N, -1);
    vec pred[N]; memset(pred, 0, sizeof(pred));
    for(int i = 0; i < N; i++){
      scanf("%d", &succ[i]);
      succ[i]--;
      pred[succ[i]].ptr = pushback(pred[succ[i]].ptr, &pred[succ[i]].sz, i);
    }
    for(int x = 0; x < N; x++){
      if (ret[x] == -1){
        int c, c2;
        for (c = x, c2 = succ[x]; c != c2 && c != succ[c2]; c = succ[c], c2 = succ[succ[c2]])
          ;
        vec cyc=newVec();
        cyc.ptr = pushback(cyc.ptr, &cyc.sz, c);
        for(int y = succ[c]; y != c; y = succ[y])
          cyc.ptr = pushback(cyc.ptr, &cyc.sz, y);
        int diff[cyc.sz]; memset(diff,0,sizeof(diff));
        int base = min(K+1, cyc.sz);
        for (int i = 0; i < cyc.sz; i++) {
          for(int z=0;z<pred[cyc.ptr[i]].sz;z++){int y = pred[cyc.ptr[i]].ptr[z];
            if (y != cyc.ptr[(i+cyc.sz-1)%cyc.sz]){
              int ns = 0;
              vec stack=newVec();
              stack.ptr=pushback(stack.ptr, &stack.sz, 0);
              void doit(int nd, int prev, int d){
                int curns = ns;
                if (stack.sz == d)
                  stack.ptr=pushback(stack.ptr, &stack.sz, 0);
                ns++;
                stack.ptr[d]++;
                for(int q=0;q<pred[nd].sz;q++){int nd2 = pred[nd].ptr[q];
                  if(nd2 != prev)
                    doit(nd2, nd, d+1);
                }
                ret[nd] = ns-curns;
                if(stack.sz == d+K+1){
                  ns -= stack.ptr[stack.sz-1];
                  stack.sz--;
                }
              }
              doit(y, cyc.ptr[i], 1);
              for (int j = 1; j < stack.sz; j++) {
                if (K-j+1 >= cyc.sz){
                  base += stack.ptr[j];
                }
                else{
                  diff[i] += stack.ptr[j];
                  diff[(i+K-j+1)%cyc.sz] -= stack.ptr[j];
                  if (i+K-j+1 >= cyc.sz)
                    base += stack.ptr[j];
                }
              }
            }
          }
        }
        for (int i = 0; i < cyc.sz; i++) {
          base += diff[i];
          ret[cyc.ptr[i]] = base;
        }
      }
    }
    for(int z=0;z<N;z++){int n = ret[z];
      printf("%d\n", n);
    }
  }
  return 0;
}
