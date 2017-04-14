#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>


#define mp make_pair
#define pb push_back


typedef long long ll;
typedef long long llong;
typedef long double ld;





enum{ MOD =(ll ) 924844033LL};
enum{ B   =(ll ) 3597LL     };
enum{ MX  =(int) 1 << 19    };

int n, m;
ll fc [MX];
ll bfc[MX];
ll dp2[120000][51];
ll dp[MX];
ll tr[MX];
ll a [MX];
ll b [MX];

void swap(ll*nums, int i, int j) {
   ll t    = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
ll pw(ll a, ll b) {
    ll ans = 1;
    while (b) {
        while (!(b & 1))
            b >>= 1, a = (a * a) % MOD;
        --b;
        ans = (ans * a) % MOD;
    }
    return ans;
}
void init() {
    fc[0] = 1;
    for (int i = 1; i < MX; ++i)
        fc[i] = (fc[i - 1] * i) % MOD;
    for (int i = 0; i < MX; ++i)
        bfc[i] = pw(fc[i], MOD - 2);
}
int rev(int x, int k) {
    int ans = 0;
    for (int i = 0; i < k; ++i) {
        ans = (ans << 1) + (x & 1);
        x >>= 1;
    }
    return ans;
}
void fft(ll *a, int n, int inv) {
    int k = 0;
    while (1 << (k + 1) <= n)
        ++k;
    for (int i = 0; i < n; ++i) {
        int x = rev(i, k);
        if (x > i)
            swap(a, x, i);
    }
    for (int bl = 1; bl < n; bl *= 2) {
        ll wadd = B;
        if (inv)
            wadd = pw(B, MOD - 2);
        wadd = pw(wadd, (1 << 21) / (2 * bl));
        for (int i = 0; i < n; i += 2 * bl) {
            ll w = 1;
            for (int j = i; j < i + bl; ++j, w = (w * wadd) % MOD) {
                ll u = a[j];
                ll v = w * a[j + bl] % MOD;
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
void run(int l, int r) {
    if (l + 1 == r) {
        if (l != 0)
            dp[l] = (dp[l] * fc[l - 1]) % MOD;
        if (l != 0 && l <= n) {
            printf("%lld\n", dp[l]);
        }
        dp[l] = dp[l] * bfc[l] % MOD;
        return;
    }
    int m = (l + r) >> 1;
    run(l, m);
    int len = (m - l) * 4;
    for (int i = 0; i < len; ++i)
        a[i] = 0, b[i] = 0;
    for (int i = 0; i < m - l; ++i)
        a[i] = dp[i + l];
    for (int i = 0; i < len / 2; ++i)
        b[i] = tr[i];
    fft(a, len, 0);
    fft(b, len, 0);
    for (int i = 0; i < len; ++i)
        a[i] = (a[i] * b[i]);
    fft(a, len, 1);
    for (int i = m - l; i < r - l; ++i)
        dp[i + l] = (dp[i + l] + a[i]) % MOD;
    run(m, r);
}
int main() {
    scanf("%d %d", &n, &m);
    dp2[0][0] = 1;
    tr[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp2[i][j] = (dp2[i - 1][j] * j + dp2[i - 1][j - 1] * j) % MOD;
        }
        tr[i] = dp2[i][m];
        if (i > 2)
            tr[i] = (tr[i] * pw(i, i - 2)) % MOD;
    }
    init();
    for (int i = 1; i <= n; ++i) {
        tr[i] = tr[i] * bfc[i - 1] % MOD;
    }
    dp[0] = 1;
    run(0, 1 << 17);
    return 0;
}



























































