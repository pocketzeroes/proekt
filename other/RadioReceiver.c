#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first;
  int second;
}pair;
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

typedef long double ld;
const double eps = 1e-10;
int R, C;
int N;
int n;


inline int comp(double a, double b){
  if(fabs(a - b) < eps)
    return 0;
  return a > b ? 1 : -1;
}
inline bool val(int i, int j){
  if(i < 0 || j < 0 || i >= R || j >= C)
    return false;
  return true;
}
int main(){
  scanf("%d", &N);
  for(int nn=1; nn<=N; ++nn){
    printf("Case #%d: ", nn);
    scanf("%d", &n);
    pair mes[n];
    for(int i=0; i<n; ++i){
      scanf("%d %d", &mes[i].second, &mes[i].first);
    }
    qsort(mes, n, sizeof(pair), cmpP);
    ld lo = 0.,
       hi = 1e9;
    while(hi-lo > 1e-10){
      ld d = (hi+lo)/2.0;
      bool val = 1;
      ld L = mes[0].second-d, 
         R = mes[0].second+d;
      int t = mes[0].first;
      for(int i=1; i<n; ++i){
        int td = mes[i].first-t;
        t = mes[i].first;
        L = fmaxl(L-td, mes[i].second-d);
        R = fminl(R+td, mes[i].second+d);
        if(comp(L,R)>0){
          val = 0;
          break;
        }
      }
      if(val)
        hi = d;
      else
        lo = d;
    }
    printf("%.11lf\n", (double)(lo+hi)/2);
  }
  return 0;
}
