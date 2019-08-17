#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

typedef struct{
  ll  first;
  int second;
}pair;
pair newPair(ll a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

typedef struct{
  int B, E;
  ll  S, T;
  double P, value;
}Route;
int cmpR(const void*pa, const void*pb){
  Route*t=(Route*)pa;
  Route*r=(Route*)pb;
  if(t->B != r->B)
    return(t->B < r->B)?-1:1;
  return(t->S < r->S)?-1:1;
}
int upper_bound(Route*a, int n, Route x){
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if(cmpR(&x, &a[mid])>=0)
            l = mid + 1;
        else
            h = mid;
    }
    return l;
}
int main(){
  int M, N;
  ll K;
  while(scanf("%d %d %lld", &M, &N, &K)==3){
    Route v[M+1];
    for(int i=0; i<M; i++){
      scanf("%d %d %lld %lld %lf", &v[i].B, &v[i].E, &v[i].S, &v[i].T, &v[i].P);
      v[i].value = 0.;
    }
    v[M].B = 1;
    v[M].S = K+1;
    v[M].value = 1.0;
    qsort(v, M+1, sizeof(Route), cmpR);
    pair ord[M+1];
    for(int i=0; i<=M; i++)
      ord[i] = newPair(-v[i].S, -i);
    qsort(ord, M+1, sizeof(pair), cmpP);
    double ret = 0.;
    for(int i=0; i<=M; i++){
      if(-ord[i].first <= K){
        int idx = -ord[i].second;
#define r v[idx]
        r.value = 0.0;
        Route r2={};
        r2.B = r.B;
        r2.S = r.S;
        int it = upper_bound(v, M+1, r2);
        if(it != M+1 && v[it].B == r.B)
          r.value += (1.0-r.P) * v[it].value;
        r2.B = r.E;
        r2.S = r.T;
        it = upper_bound(v, M+1, r2);
        if(it != M+1 && v[it].B == r.E)
          r.value += r.P * v[it].value;
        if(idx < M && v[idx+1].B == v[idx].B)
          r.value = fmax(r.value, v[idx+1].value);
        if(r.B == 0)
          ret = fmax(ret, r.value);
      }
    }
    printf("%0.8lf\n", ret);
  }
  return 0;
}
