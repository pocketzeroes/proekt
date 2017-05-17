#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


#define ll long long
#define pb push_back
#define mp make_pair
#define def 400000
#define maxN (def + 18)
#define mod 666013

#define SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

typedef struct zoneS {
    int x1, y1, x2, y2;
}zone;

void frumusel(zone z){
    if (z.x1 > z.x2) SWAP(z.x1, z.x2);
    if (z.y1 > z.y2) SWAP(z.y1, z.y2);
}


zone Z1,Z2;
ll fact[maxN], inv_fact[maxN];
ll ans;
ll poww(ll a, ll b) {
    ll ans = 1;
    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return ans;
}
void pre() {
    ll i;
    fact[0] = 1;
    for (i = 1; i <= def; i++) fact[i] = (fact[i - 1] * i) % mod;
    inv_fact[def] = poww(fact[def], mod - 2);
    for (i = def - 1; i > 0; i--) inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;
    inv_fact[0] = 1;
}
ll comb(ll n, ll k){
    if (k > n) return 0;
    if (k < 0) return 0;
    if (n > def) return 0;
    ll ans = (fact[n] * inv_fact[n - k]) % mod;
    ans = (ans * inv_fact[k]) % mod;
    return ans;
}
ll get_intr(ll x, ll y, ll xx, ll yy) {
    x = max(x, xx);
    y = min(y, yy);
    return max(0LL, y - x + 1);
}
ll sum_comb(ll n1, ll k, ll n2) {
    ll ans = mod + comb(n2 + 1, k + 1) - comb(n1, k + 1);
    return ans % mod;
}
void solve() {
    ll i, j, delta, lini, rini, dif, abs_delta;
    zone aux, aux2;
    ll act;
    for (delta = -100003; delta <= 100003; delta++) {
        aux = Z2;
        aux.x1 += delta;
        aux.x2 += delta;
        abs_delta = (delta > 0 ? delta : -delta);
        ll common = get_intr(Z1.x1, Z1.x2, aux.x1, aux.x2);
        if (common == 0) continue;
        if (get_intr(Z1.y1, Z1.y2, aux.y1, aux.y2) != 0) {
            continue;
        }
        aux2 = Z1;
        if (aux.y1 > aux2.y1){
            zone ttt=aux;
            aux=aux2;
            aux2=ttt;
        }
        lini = aux2.y1 - aux.y2;
        rini = aux2.y2 - aux.y2;
        dif = aux.y2 - aux.y1;
        act = sum_comb(abs_delta + rini + 1, abs_delta + 1, abs_delta + rini + 1 + dif);
        act -= sum_comb(abs_delta + lini, abs_delta + 1, abs_delta + lini + dif);
        act += mod;
        act = (act * common) % mod;
        ans += act;
        ans %= mod;
    }
}
int main()
{
    scanf("%d%d%d%d", &Z1.x1, &Z1.y1, &Z1.x2, &Z1.y2);
    scanf("%d%d%d%d", &Z2.x1, &Z2.y1, &Z2.x2, &Z2.y2);
    frumusel(Z1);
    frumusel(Z2);
    if (get_intr(Z1.y1, Z1.y2, Z2.y1, Z2.y2) != 0) {
        SWAP(Z1.x1, Z1.y1);
        SWAP(Z1.x2, Z1.y2);
        SWAP(Z2.x1, Z2.y1);
        SWAP(Z2.x2, Z2.y2);
    }
    pre();
    solve();
    printf("%lld", ans);
    return 0;
}





















































