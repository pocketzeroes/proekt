#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

ll in_nextLong(){
  ll x;
  scanf("%lld", &x);
  return x;
}

int main(){
    ll n = in_nextLong();
    ll m = in_nextLong();
    ll a = in_nextLong();
    ll b = n*m-a;
    if(a == 0 || a == n*m)
        puts("0");
    else if(a%n == 0 || a%m == 0)
        puts("1");
    else{
        if(n > m){
            ll t = n; n = m; m = t;//swap
        }
        int r = 3;
        for(ll x = 1; x*x <= a; x++)
            if(a%x == 0 && x <= n && a/x <= m)
                r = 2;
        for(ll x = 1; x*x <= b; x++)
            if(b%x == 0 && x <= n && b/x <= m)
                r = 2;
        printf("%d\n", r);
    }
    return 0;
}
