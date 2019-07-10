#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

int main(){
  vecl V = newVecL();
  ll n;
  scanf("%lld", &n);
  ll a = 1, b = 1;
  while(b <= n){
    V.ptr = pushbackL(V.ptr, &V.sz, b);
    ll tmp = b;
    b = a+b;
    a = tmp;
  }
  ll last = -1;
  for(int i = V.sz-1; i >= 0; --i){
    if(n-V.ptr[i] >= 0)
      n -= (last = V.ptr[i]);
  }
  printf("%lld\n", last);
  return 0;
}
