#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}


int main(){
    int n;
    scanf("%d", &n);
    ll a[n];
    int asz = n;
    for(int i = 0; i < n; ++i)
        scanf("%lld", &a[i]);
    ll res = 0;
    for(int b = 62; b >= 0; --b){
        qsort(a, asz, sizeof(ll), cmpLL);
        if(a[asz-1] >= 1ll<<b){
            if(!(res & 1ll<<b))
                res ^= a[asz-1];
            for(int i = asz-2; i>=0 && a[i] >= 1ll<<b; --i)
                a[i] ^= a[asz-1];
            asz--;
            if(asz==0)
                break;
        }
    }
    printf("%lld\n", res);
    return 0;
}
