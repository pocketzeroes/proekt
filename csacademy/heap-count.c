#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ MOD = (ll)1e9 + 7};
enum{ N   = 100100};
int sz[N];
ll heaps[N];
int n, X, Y;
ll dp[2][N];
ll f[N], rf[N];

ll add(ll x, ll y) {
    x += y;
    if (x >= MOD) return x - MOD;
    return x;
}
ll sub(ll x, ll y) {
    x -= y;
    if (x < 0) return x + MOD;
    return x;
}
ll mult(ll x, ll y) {
    return (x * y) % MOD;
}
ll bin_pow(ll x, ll p) {
    if (p == 0) return 1;
    if (p & 1) return mult(x, bin_pow(x, p - 1));
    return bin_pow(mult(x, x), p / 2);
}
ll rev(ll x) {
    return bin_pow(x, MOD - 2);
}
ll getC(int n, int k) {
    if (k < 0 || k > n) return 0;
    return mult(f[n], mult(rf[k], rf[n - k]));
}
int main() {
    f[0] = 1;
    for (int i = 1; i < N; i++)
        f[i] = mult(f[i - 1], i);
    rf[N - 1] = rev(f[N - 1]);
    for (int i = N - 1; i > 0; i--)
        rf[i - 1] = mult(rf[i], i);
    scanf("%d%d%d", &n, &X, &Y);
    for (int i = n; i >= 1; i--)
        heaps[i] = 1;
    for (int i = n; i >= 1; i--) {
        if (sz[i] > 0)
            heaps[i] = mult(heaps[i], getC(sz[i], sz[2 * i]));
        sz[i]++;
        if (i > 1) {
            sz[i / 2] += sz[i];
            heaps[i / 2] = mult(heaps[i / 2], heaps[i]);
        }
    }
    ll coeff = heaps[X];
    dp[0][Y] = getC(n - Y, sz[X] - 1);
    while(X > 1) {
        int Z = X / 2;
        int v = Z * 2;
        if (v == X) v++;
        if (v <= n) coeff = mult(coeff, heaps[v]);
        ll sum = 0;
        for (int i = 1; i <= n; i++)
            dp[1][i] = 0;
        for (int i = n - 1; i > 0; i--) {
            sum = add(sum, dp[0][i + 1]);
            dp[1][i] = mult(sum, getC(n - i - sz[X], sz[Z] - sz[X] - 1));
        }
        X = Z;
        for (int i = 1; i <= n; i++)
            dp[0][i] = dp[1][i];
    }
    printf("%lld\n", mult(coeff, dp[0][1]));
    return 0;
}

























































