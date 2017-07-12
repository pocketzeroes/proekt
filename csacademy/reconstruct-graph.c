#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef long long ll;

enum{ maxn =(ll) 1e6 + 100};
enum{ mod  =(ll) 1e9 + 7  };
ll val   [maxn];
ll pocket[maxn];
ll some1 [maxn];
ll pow2  [maxn];
ll in    [maxn];
ll res = 1;

ll ppow(ll a, ll b, ll mod){
    if(b == 0){
        return 1;
    }
    if(b % 2 == 1){
        return (ppow((a * a) % mod, b / 2, mod) * a) % mod;
    }
    else {
        return ppow((a * a) % mod, b / 2, mod);
    }
}

int main(){
    ll n, e;
    scanf("%lld %lld", &n, &e);
    pow2[0] = 1;
    for(ll i = 1; i < maxn; i++){
        pow2[i] = 2 * pow2[i - 1];
        pow2[i] %= mod;
    }
    for(ll i = 0; i < n; i++){
        scanf("%lld", &val[i]);
        pocket[val[i]]++;
    }
    if(pocket[0] != 1){
        puts("0");
        return 0;
    }
    for(ll i = n - 1; i > 0; i--){
        if(pocket[i] && !pocket[i - 1]){
            puts("0");
            return 0;
        }
    }
    for(ll i = 0; i < e; i++){
        ll f, s;
        scanf("%lld %lld", &f, &s);
        f--, s--;
        if(val[f] == val[s]){
            some1[val[f]]++;
        }
        else if(val[f] + 1 == val[s]){
            in[s]++;
        }
        else if(val[s] + 1 == val[f]){
            in[f]++;
        }
        else {
            puts("0");
            return 0;
        }
    }
    for(ll i = 0; i < n; i++){
        if(val[i] != 0){
            ll get = pocket[val[i] - 1] - in[i];
            if(in[i] == 0){
                get = pow2[get] - 1;
            }
            else {
                get = pow2[get];
            }
            res *= get;
            res %= mod;
        }
    }
    for(ll i = 0; i < n; i++){
        ll part = pocket[i] * (pocket[i] - 1) / 2;
        part -= some1[i];
        part = ppow(2, part, mod);
        res *= part;
        res %= mod;
    }
    printf("%lld\n", res);
}





























