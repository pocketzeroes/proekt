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
}Pair;
Pair newPair(ll a, ll b){
  Pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Pair*pushbackP(Pair*array, int *size, Pair value){
  Pair*output = resizeArray(array, Pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmp(const void*pa, const void*pb){
  Pair*px=(Pair*)pa;
  Pair*py=(Pair*)pb;
  Pair x = *px;
  Pair y = *py;
  if(x.first*y.second == y.first*x.second)
    return(x.first < y.first)?-1:1;
  return(x.first*y.second < y.first*x.second)?-1:1;
}

int main(){
  ll f, b;
  scanf("%lld %lld", &f, &b);
  ll F[f];
  ll B[b];
  for(ll i = 0; i < f; ++i)
    scanf("%lld", &F[i]);
  for(ll i = 0; i < b; ++i)
    scanf("%lld", &B[i]);
  vecp arr = newVecP();// Pair ll ll
  for(ll i=0; i<f; ++i)
    for(ll j=0; j<b; ++j)
      arr.ptr = pushbackP(arr.ptr, &arr.sz, newPair(F[i], B[j]));
  qsort(arr.ptr, arr.sz, sizeof(Pair), cmp);
  for(int z=0;z<arr.sz;z++){Pair p = arr.ptr[z];
    printf("(%lld,%lld)\n", p.first, p.second);
  }
  return 0;
}
