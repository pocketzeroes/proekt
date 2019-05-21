#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) (((a)>(b))?(a):(b))

typedef long long ll;

enum{ MN = 100111};
ll n, m, a[MN], sum[MN];

signed main(){
    ll ntest;
    scanf("%lld", &ntest);
    while(ntest--){
        scanf("%lld %lld", &n, &m);
        for(ll i = (1), _b = (n); i <= _b; ++i){
            scanf("%lld", &a[i]);
            sum[i] = sum[i-1] + a[i];
        }
        ll res = 0;
        for (ll i = (1), _b = (n); i <= _b; ++i){
          if (a[i] == m) {
            ll left  = i,
               right = i;
            while (left  > 1 && a[left -1] > a[i]) --left ;
            while (right < n && a[right+1] > a[i]) ++right;
            res = max(res, sum[right] - sum[left-1]);
          }
        }
        printf("%lld\n", res);
    }
    return 0;
}
