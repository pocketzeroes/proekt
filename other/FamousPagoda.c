#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

ll rand16(){
    return rand() & ((1LL<<(16)) - 1);
}
ll my_rand(){
    return rand16() << 32 | rand16() << 16 | rand16();
}

ll n, g, k;
enum{ MN = 2011};
ll cost[MN][MN], a[MN], dp[MN][MN], sum[MN], sum2[MN];

ll getSum(ll l, ll r){
    return sum[r] - sum[l-1];
}
ll getSum2(ll l, ll r) {
    return sum2[r] - sum2[l-1];
}
void init1() {
    for (ll i = (1), _i = (n); i <= _i; ++i) {
        for (ll j = (i), _j = (n); j <= _j; ++j) {
            ll mid = i + (j - i + 1) / 2;
            cost[i][j] = a[mid] * (mid - i + 1LL) - getSum(i, mid) + getSum(mid, j) - a[mid] * (j - mid + 1LL);
        }
    }
}
void init2(){
    for (ll i = (1), _i = (n); i <= _i; ++i) {
        for (ll j = (i), _j = (n); j <= _j; ++j) {
            ll A = j - i + 1;
            ll B = -2 * getSum(i, j);
            ll approx_v = -B / (2 * A);
            cost[i][j] = 1e18;
            for (ll v = (approx_v - 2), _v = (approx_v + 2); v <= _v; ++v) {
                ll cur = getSum2(i, j) + A * v * v - 2 * getSum(i, j) * v;
                cost[i][j] = min(cost[i][j], cur);
            }
        }
    }
}
void compute(ll i, ll L, ll R, ll optL, ll optR) {
    if (L > R)
        return;
    ll mid = (L + R) >> 1, savek = optL;
    dp[i][mid] = 1e18;
    for (ll k = (optL), _k = (min(mid-1, optR)); k <= _k; ++k) {
        ll cur = dp[i-1][k] + cost[k+1][mid];
        if (cur < dp[i][mid]) {
            dp[i][mid] = cur;
            savek = k;
        }
    }
    compute(i, L, mid-1, optL, savek);
    compute(i, mid+1, R, savek, optR);
}
int main(){
    scanf("%lld%lld%lld", &n, &g, &k);
    for (ll i = (1), _i = (n); i <= _i; ++i)
        scanf("%lld", &a[i]);
    for (ll i = (1), _i = (n); i <= _i; ++i)
        sum[i] = sum[i-1] + a[i];
    for (ll i = (1), _i = (n); i <= _i; ++i)
        sum2[i] = sum2[i-1] + a[i] * a[i];
    if (k == 1)
        init1();
    else
        init2();
    for (ll i = (0), _i = (n); i <= _i; ++i)
        for (ll j = (0), _j = (n); j <= _j; ++j)
            dp[i][j] =(ll)1e18;
    for (ll i = (1), _i = (n); i <= _i; ++i)
        dp[1][i] = cost[1][i];
    for (ll i = (2), _i = (g); i <= _i; ++i)
        compute(i, 1, n, 0, n);
    printf("%lld\n", dp[g][n]);
    return 0;
}
