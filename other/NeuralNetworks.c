#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ MOD = 998244353};
int N, arr [500010];
ll fact [500010], invfact [500010], powa [500010], ret = 1;


ll fastPow(ll base, ll expo){
    base %= MOD;
    if(expo == 0)
        return 1;
    ll halfy = fastPow(base, expo/2);
    ll bro = expo%2 ? base : 1;
    return(((halfy*halfy)%MOD)*bro)%MOD;
}
ll modInverse(ll x){
    return fastPow(x, MOD-2);
}
ll choose(ll n, ll k){
    return(((fact[n]*invfact[k])%MOD)*invfact[n-k])%MOD;
}
int main(){
    scanf("%d", &N);
    fact[0] = invfact[0] = powa[0] = 1;
    for(int i=0; i<N; i++)
        scanf("%d", &arr[i]);
    for(int i=1; i<=500000; i++){
        powa[i] = (powa[i-1]*2)%MOD;
        fact[i] = (fact[i-1]*(ll)i)%MOD;
        invfact[i] = (invfact[i-1]*modInverse((ll)i))%MOD;
    }
    for(int i=1; i<N; i++){
        ll a = arr[i-1],
           b = arr[i];
        ll mult = 0,
           signy = 1;
        for(ll num=a; num>0; num--){
            ll combi = choose(a, num);
            ll val = (combi*fastPow(powa[num]-1+MOD, b))%MOD;
            mult += (val*signy)%MOD+MOD; mult %= MOD; signy = -signy;
        }
        ret = (ret*mult)%MOD;
    }
    printf("%lld\n", ret);
    return 0;
}
