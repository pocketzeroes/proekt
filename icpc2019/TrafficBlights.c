#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*a,int sz,int val){
  for(int i=0;i<sz;i++)a[i]=val;
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
vec *pushback2d(vec *array, int *size, vec value) {
  vec *output = resizeArray(array, vec, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  vec*ptr;
  int sz;
}vec2d;
vec2d newVec2d() {
  vec2d rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

#define SPLIT (5*7*8*9)

int Gcd(int a, int b) { return b ? Gcd(b, a%b) : a; }

int main(){
  int N;
  while(scanf("%d", &N)==1){
    vec2d filters = newVec2d();
    int X [N];
    int R [N];
    int G [N];
    int fn[N]; fill(fn, N, -1);
    for(int i = 0; i < N; i++) {
      scanf("%d %d %d", &X[i], &R[i], &G[i]);
      int period = (R[i]+G[i])/Gcd(SPLIT, R[i]+G[i]);
      for (int j = 0; j < filters.sz; j++){
        if(period % filters.ptr[j].sz == 0){
          filters.ptr[j].sz = period;
          if(filters.ptr[j].ptr)free(filters.ptr[j].ptr);
          filters.ptr[j].ptr = calloc(period, sizeof(int));
          fill(filters.ptr[j].ptr, period, -1);
        }
        if (filters.ptr[j].sz % period == 0){
          fn[i] = j;
          break;
        }
      }
      if (fn[i] == -1){
        fn[i] = filters.sz;
        vec nv = newVec();
        for(int z=0; z<period; z++)
          nv.ptr=pushback(nv.ptr, &nv.sz, -1);
        filters.ptr = pushback2d(filters.ptr, &filters.sz, nv);
      }
    }
    double ret[N+1]; memset(ret,0,sizeof(ret));
    for(int base = 0; base < SPLIT; base++) {
      double cur = 1.0/SPLIT;
      for(int i = 0; i < N; i++){
   #define  filter filters.ptr[fn[i]]
        int tot = 0, filtered = 0;
        for (int j = 0, t = SPLIT+base+X[i]; j < filter.sz; j++, t += SPLIT){
          if (filter.ptr[j] < base){
            tot++;
            if (t%(R[i]+G[i]) < R[i]){
              filter.ptr[j] = base;
              filtered++;
            }
          }
        }
        double oldCur = cur;
        if (tot)
          cur *= (double)(tot-filtered) / tot;
        ret[i] += oldCur-cur;
      }
      ret[N] += cur;
    }
    for(int z=0;z<N+1;z++){double p = ret[z];
      printf("%.9lf\n", p);
    }
  }
  return 0;
}
