#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int *array, int *size, int value){
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
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
int N,M;
vec V;
vec S;

int main(){
  int i, x;
  scanf("%d %d", &N, &M);
  for(i=0; i<N; i++){
    scanf("%d", &x);
    V.ptr = pushback(V.ptr, &V.sz, x);
  }
  qsort(V.ptr, V.sz, sizeof(int), cmp);
  for(i=0; i<N; i++)
    V.ptr[i] -= i;
  for(i=0; i<N; i++)
    V.ptr = pushback(V.ptr, &V.sz, V.ptr[i]+(M-N));
  for(i=0; i<N; i++)
    V.ptr = pushback(V.ptr, &V.sz, V.ptr[i]+2*(M-N));
  for(int z=0; z<V.sz; z++){int v=V.ptr[z];
    if(S.sz){
      S.ptr = pushback(S.ptr, &S.sz, S.ptr[S.sz-1]+v);
    }
    else{
      S.ptr = pushback(S.ptr, &S.sz, v);
    }
  }
  ll mi = 1LL<<60;
  for(i=N; i<2*N; i++){
    mi = min(mi, (S.ptr[i+N/2]-S.ptr[i]-V.ptr[i]*(N/2))+(V.ptr[i]*(N-N/2)-(S.ptr[i]-S.ptr[i+N/2-N])));
  }
  printf("%lld\n", mi);
  return 0;
}
