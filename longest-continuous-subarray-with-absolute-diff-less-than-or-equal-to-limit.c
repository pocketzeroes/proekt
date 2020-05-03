#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int asz;

int rmq(int**or, int l, int r){
    assert(l <= r);
    if(l >= r)
        return INT_MAX;
    int t = 31-__builtin_clz(r-l);
    return fmin(or[t][l], or[t][r-(1<<t)]);
}
bool ok(int h, int*a, int lim, int**st, int**str){
    int n = asz;
    for(int i=0; i<n-h+1; i++){
        if(-rmq(str, i, i+h) - rmq(st, i, i+h) <= lim)
            return true;
    }
    return false;
}
int**build(int*a){
    int n = asz;
    int b = 32-__builtin_clz(n);
    int**ret = calloc(b, sizeof(int*));
    for(int i=0,l=1; i<b; i++,l*=2){
        if(i == 0)
            ret[i] = a;
        else{
            ret[i] = calloc(n-l+1, sizeof(int));
            for(int j=0; j<n-l+1; j++){
                ret[i][j] = fmin(ret[i-1][j], ret[i-1][j+l/2]);
            }
        }
    }
    return ret;
}

int longestSubarray(int*a, int aSz, int limit){
    asz = aSz;
    int n = aSz;
    int low  = 1,
        high = n+1;
    int**st = build(a);
    int*ra = calloc(n, sizeof(int));
    for(int i=0; i<n; i++)
        ra[i] = -a[i];
    int**str = build(ra);
    while(high - low > 1){
        int h = high+low>>1;
        if(ok(h, a, limit, st, str))
            low = h;
        else
            high = h;
    }
    return low;
}
//int main(){
//    return 0;
//}

