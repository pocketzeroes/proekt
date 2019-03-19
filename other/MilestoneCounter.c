#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int cmpL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
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

ll p[1000000];
ll x[1000000];

int main(){
    int m,n;
    scanf("%d %d", &m, &n);
    for(int i=0; i<m; i++)
        scanf("%ld", &p[i]);
    for(int i=0; i<n; i++)
        scanf("%ld", &x[i]);
    vecl res = newVecL();
    for(int i=0; i+m<=n; i++){
        bool ok=true;
        for(int j=2; j<m; j++){
            if((x[i+j]-x[i+j-1])*(__int128)(p[1]-p[0]) != (x[i+1]-x[i])*(__int128)(p[j]-p[j-1])){
                ok=false;
                break;
            }
        }
        if(ok){
            res.ptr = pushbackL(res.ptr, &res.sz, x[i+1]-x[i]);
        }
    }
    int answer = !!res.sz;
    qsort(res.ptr, res.sz, sizeof(ll), cmpL);
    for(int i=1; i<res.sz; i++)
        answer += (res.ptr[i]!=res.ptr[i-1]);
    printf("%d\n", answer);
    for(int i=0; i<res.sz; i++)
        if(i==0 || res.ptr[i]!=res.ptr[i-1])
            printf("%lld%c", res.ptr[i], (--answer?' ':'\n'));
    if(!answer)
        puts("");
    return 0;
}
