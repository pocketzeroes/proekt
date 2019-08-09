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
int cmpL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}

ll* R;
int Rsz;
vecl K;

void choose(ll u, int h){
    ll l = u * (ll)1 << h;
    ll r = (u * (ll)1 << h) + ((ll)1 << h) - 1;
    bool found = false;
    for (int i = 0; i < Rsz && !found; i++)
        if (l <= R[i] && R[i] <= r)
            found = true;
    if (!found)
        K.ptr = pushbackL(K.ptr, &K.sz, u);
    else if(l < r){
        choose(2 * u, h - 1);
        choose(2 * u + 1, h - 1);
    }
}
int main(){
    int n, r;
    scanf("%d %d", &n, &r);
    R = calloc(r, sizeof(ll));
    Rsz=r;
    for(int i=0; i<r; i++)
        scanf("%lld", &R[i]);
    K = newVecL();
    choose(1, n);
    qsort(K.ptr, K.sz, sizeof(ll), cmpL);
    for (int i = 0; i < K.sz; i++){
        if (i > 0)
            printf(" ");
        printf("%lld", K.ptr[i]);
    }
    puts("");
    return 0;
}
