#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

void swap(ll*nums, int i, int j) {
   ll t    = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}

enum{ MAXN = 510000};
#define MOD 998244353LL
ll B = 662;
ll f  [MAXN];
ll g  [MAXN];
ll ans[MAXN];
ll fc [MAXN];
int n, q;


ll   pw (ll a, ll b){
    ll ans = 1; 
    while (b) {
        while(!(b & 1))
            b >>= 1, a = (a * a) % MOD;
        ans = (ans * a) % MOD, --b;
    }
    return ans;
}
int  rev(int x, int k){
    int ans = 0;
    for (int i = 0; i < k; ++i) {
        ans = (ans * 2) + (x & 1);
        x >>= 1;
    }
    return ans;
}
void fft(ll *a, int k, int inv){
    int n = (1 << k);
    for (int i = 0; i < n; ++i) {
        int x = rev(i, k);
        if (x > i)
            swap(a, x, i);
    }
    for (int bl = 1; bl < n; bl *= 2) {
        ll wadd = pw(B, (1 << 21) / bl);
        if (inv)
            wadd = pw(wadd, MOD - 2);
        for (int i = 0; i < n; i += 2 * bl) {
            ll w = 1;
            for (int j = i; j < i + bl; ++j, w = (w * wadd) % MOD) {
                ll u = a[j];
                ll v = a[j + bl] * w % MOD;
                a[j] = (u + v) % MOD;
                a[j + bl] = (u - v + MOD) % MOD;
            }
        }
    }
    if (inv) {
        ll x = pw(n, MOD - 2);
        for (int i = 0; i < n; ++i)
            a[i] = (a[i] * x) % MOD;
    }
}
int main(){
    scanf("%d %d", &n, &q);
    fc[0] = 1;
    for (int i = 1; i <= n; ++i)
        fc[i] = (fc[i - 1] * i) % MOD;
    for (int i = 0; i < n - 1; ++i)
        f[i] = (n - i - 1) / 2 * fc[n - i - 2] % MOD;
    for (int i = 0; i < n; ++i)
        g[i] = pw(fc[i], MOD - 2);
    int k = 0;
    while ((1 << k) <= 2 * n + 1)
        ++k;
    fft(f, k, 0);
    fft(g, k, 0);
    for (int i = 0; i < (1 << k); ++i)
        f[i] = (f[i] * g[i]) % MOD;
    fft(f, k, 1);
    for (int i = 1; i <= n; ++i) {
        ans[i] = fc[n - i] * f[n - i] % MOD;
    }
    for (int i = 0; i < q; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%lld\n", ans[y]);
    }
    return 0;
}


