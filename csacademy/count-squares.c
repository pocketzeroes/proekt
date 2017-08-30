#include <stdio.h>

typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

int main(){
    ll n, m, sol;
    ll MOD = 1e9 + 7;
    scanf ("%lld %lld", &n, &m);
    for (int i = 1; i <= min(n, m); i++){
        sol = (sol + ((n-i+1) * (m-i+1)) % MOD) % MOD;
        sol += (((n-i+1) * (m-i+1)) % MOD * (i-1)) % MOD;
        sol %= MOD; 
    }
    printf ("%lld\n", sol);
	return 0;
}
