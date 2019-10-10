#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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
//////////////////
typedef long long ll;

ll incex(int at, int prod, int par, vec*p, int a, int b, int c, int d){
   ll r = par*(b/prod-a/prod)*(ll)(d/prod-c/prod);
   int lim = fmin(b, d) / prod;
   for(int i=at; i<p->sz && p->ptr[i] <= lim; i++)
      r += incex(i+1, prod *p->ptr[i], -par, p, a, b, c, d);
   return r;
}
int main(){
   int A, B, C, D;
   scanf("%d%d%d%d", &A, &B, &C, &D);
   int HI = fmin(B, D);
   vec primes = newVec();
   char sf[HI+1]; clr(sf);
   pb(primes, 2);
   for(ll i=3; i<=HI; i += 2){
      if(sf[i] == 0){
         pb(primes, i);
         sf[i] = 1;
         if(HI / i >= i)
            for(ll j=i*i; j<=HI; j += 2*i)
               sf[j] = 1;
      }
   }
   printf("%lld\n", incex(0, 1, 1, &primes, A-1, B, C-1, D));
   return 0;
}
