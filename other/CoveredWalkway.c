#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
typedef struct{
  ll first;
  ll second;
}pair;
pair newPair(ll a, ll b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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
enum{ MAXN = 1000100};

ll X[MAXN];
ll Y[MAXN];

void conv_insert(int ii, vecp*C, pair x){
  while(C->sz - ii > 1){
    int i = C->sz - 2;
    int j = C->sz - 1;
    if((C->ptr[j].second - C->ptr[i].second) / (C->ptr[i].first - C->ptr[j].first) < (C->ptr[j].second - x.second) / (x.first - C->ptr[j].first))
      C->sz--;
    else
      break;
  }
  C->ptr = pushbackP(C->ptr, &C->sz, x);
}
ll eval(pair v, int x){
  return v.second + x * v.first;
}
int main(){
  int N, K;
  for(scanf("%d%d", &N, &K);;){
    for(int i = 0; i < N; i++)
      scanf("%lld", &X[i]);
    int ii = 0;
    vecp C = newVecP();
    C.ptr = pushbackP(C.ptr, &C.sz, newPair(-2 * X[N - 1], X[N - 1] * X[N - 1]));
    for(int i = N - 1; ; i--){
      while(C.sz - ii > 1 && eval(C.ptr[ii], X[i]) > eval(C.ptr[ii + 1], X[i]))
        ii++;
      ll v = K + X[i] * X[i] + eval(C.ptr[ii], X[i]);
      if(i == 0){
        printf("%lld\n", v);
        break;
      }
      conv_insert(ii, &C, newPair(-2 * X[i - 1], v + X[i - 1] * X[i - 1]));
    }
    break;
  }
  return 0;
}
