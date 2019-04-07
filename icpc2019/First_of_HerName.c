#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
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
typedef struct{
  pair first;
  int second;
}trip;
trip newTrip(pair a, int b){
  trip rez;
  rez.first  = a;
  rez.second = b;
  return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int cmpT(const void*pa, const void*pb){
  trip*a=(trip*)pa;
  trip*b=(trip*)pb;
  int rv = cmpP(&a->first, &b->first);
  if(rv!=0)
    return rv<0?-1:1;
  return a->second < b->second?-1:1;
}



int main(){
  int N, K;
  while(scanf("%d %d", &N, &K)==2){
    int suffix[N+1]; fill(suffix, N+1, -1);
    int succ  [N+1]; memset(succ, 0, sizeof(succ));
    char S[N+1];     memset(S, 0, sizeof(S));
    for(int i = 1; i <= N; i++){
      getchar();
      scanf("%c %d", &S[i], &succ[i]);
      suffix[i] = S[i];
    }
    int succ2[N+1];
    memcpy(succ2, succ, sizeof(succ));
    for(int sz = 1; sz <= N; sz <<= 1){
      trip v[N+1]; memset(v, 0, sizeof(v));
      for(int i = N; i >= 0; i--){
        v[i] = newTrip(newPair(suffix[i], suffix[succ2[i]]), i);
        succ2[i] = succ2[succ2[i]];
      }
      qsort(v, N+1, sizeof(trip), cmpT);
      for(int i = 0, cur = 0; i < N+1; i++){
        if (i > 0 && cmpP(&v[i-1].first, &v[i].first)!=0)
          cur++;
        suffix[v[i].second] = cur;
      }
    }
    vecp order = newVecP();
    for(int i=0; i<N+1; i++)
      order.ptr = pushbackP(order.ptr, &order.sz, newPair(suffix[i], i));
    qsort(order.ptr, order.sz, sizeof(pair), cmpP);
    for(int i=0; i<K; i++){
      char*s = getstr();
      int cmp(int p){
        for (int i = 0; s[i]; i++, p = succ[p]){
          if (s[i] != S[p])
            return s[i] < S[p] ? -1 : 1;
        }
        return 0;
      }
      int lo, hi;
      for(lo = 0, hi = N+1; lo < hi; ){
        int mid = (lo+hi)/2;
        if(cmp(order.ptr[mid].second) > 0)
          lo = mid+1;
        else
          hi = mid;
      }
      int start = lo;
      for(lo = 0, hi = N+1; lo < hi;){
        int mid = (lo+hi)/2;
        if(cmp(order.ptr[mid].second) >= 0)
          lo = mid+1;
        else
          hi = mid;
      }
      printf("%d\n", lo-start);
    }
  }
  return 0;
}
