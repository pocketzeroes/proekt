#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

ll n_milk, milk[10111];
ll n_topping, topping[10111];
int main(){
    scanf("%lld", &n_milk);
    for(ll i = 1, _i = (n_milk); i <= _i; ++i){
        scanf("%lld", &milk[i]);
    }
    scanf("%lld", &n_topping);
    for(ll i = 1, _i = (n_topping); i <= _i; ++i){
        scanf("%lld", &topping[i]);
    }
    ll min_cost = 1000111000111LL;
    for(ll i = 1, _i = (n_milk); i <= _i; ++i){
        ll k; 
        scanf("%lld", &k);
        for(ll j = 1, _j = (k); j <= _j; ++j){
            ll id;
            scanf("%lld", &id);
            min_cost = fminl(min_cost, milk[i] + topping[id]);
        }
    }
    ll X; 
    scanf("%lld", &X);
    printf("%lld", (ll)fmaxl(X/min_cost - 1, 0LL) );
    return 0;
}
