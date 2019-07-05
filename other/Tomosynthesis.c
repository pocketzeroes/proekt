#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
double min(double a, double b){return a<b?a:b;}
double max(double a, double b){return a>b?a:b;}
double sqr(double x){return x*x;}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct{
  double first;
  double second;
}pair;
pair newPair(double a, double b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
///////////////////

int main(){
  double x[200], y[200], r[200];
  int N;
  vecp ival = newVecP();
  scanf("%d", &N);
  for(int i = 0; i < N; ++i)
    scanf("%lf %lf %lf", x+i, y+i, r+i);
  for(int i = 0; i < N; ++i){
    for(int j = 0; j < N; ++j){
      if(i == j) 
        continue;
      double d = sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
      double v = atan2(y[j]-y[i], x[j]-x[i]);
      double th = M_PI/2-acos((r[i]+r[j])/d);
      ival.ptr = pushbackP(ival.ptr, &ival.sz, newPair(v-2*M_PI-th, v-2*M_PI+th));
      ival.ptr = pushbackP(ival.ptr, &ival.sz, newPair(v-th, v+th));
      ival.ptr = pushbackP(ival.ptr, &ival.sz, newPair(v+2*M_PI-th, v+2*M_PI+th));
    }
  }
  qsort(ival.ptr, ival.sz, sizeof(pair), cmpP);
  double res = 0, at = ival.ptr[0].first;
  for(int i = 0; i < ival.sz;){
    int j = i;
    if (at > -M_PI && at < M_PI)
      res = max(res, ival.ptr[i].first-at);
    double end = ival.ptr[i].second;
    while (j+1 < ival.sz && ival.ptr[j+1].first <= end)
      end = max(end, ival.ptr[j+1].second), ++j;
    at = end;
    i = j+1;
  }
  printf("%.10lf\n", res);
  return 0;
}
