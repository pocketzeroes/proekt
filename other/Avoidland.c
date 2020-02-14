#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;
ll n;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
#define pbl(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
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

ll process(ll*v){
    vecl doubled=newVecL();
    vecl missing=newVecL();
    for(int i=1; i<n+1; i++){
        if(v[i] == 0)
           pbl(missing, i);
        for(int j=v[i]; j>1; j--)
           pbl(doubled, i);
    }
    ll total=0;
    for(int i=0; i<doubled.sz; i++)
        total += llabs(doubled.ptr[i] - missing.ptr[i]);
    return total;
}
int main(){
    scanf("%lld", &n);
    ll hz[n+1]; clr(hz);
    ll vt[n+1]; clr(vt);
    for(int i=0; i<n; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        hz[x]++;
        vt[y]++;
    }
    ll total = 0;
    total += process(hz);
    total += process(vt);
    printf("%lld\n", total);
    return 0;
}
