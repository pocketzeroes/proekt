#pragma GCC optimize "-O3"
#include<stdio.h>
#include<time.h>
#include<stdbool.h>
typedef unsigned long long ll;

enum{ N = 11111};
#define inf 1ULL<<63

ll K, n, i, a[N], ans = inf;
int m;
int ED = 3.9 * CLOCKS_PER_SEC;

inline ll mul(ll a, ll b){
    if (a>ans / b)
        return ans;
    return a*b;
}
inline bool cal(ll ret, ll x, ll base, ll now){
    while (ret >= x){
        now += mul(base, x);
        base = mul(base, K);
        if (now >= ans)
            return 0;
        ret /= x;
    }
    return 1;
}
void dfs(int x, ll base, ll ret, ll n) {
    if (ret >= ans)
        return;
    if (clock() > ED)
        return;
    if (n == 1) {
        ans = ret;
        return;
    }
    if (base >= ans)
        return;
    while (1){
        while (x <= m&&n%a[x])
            x++;
        if (x>m)
            return;
        ll t = ret + mul(base, a[x]);
        if (t >= ans)
            return;
        if (!cal(n, a[x], base, ret))
            return;
        dfs(x, mul(base, K), t, n / a[x]);
        if (clock() > ED)
            return;
        x++;
    }
}
int main(){
    scanf("%llu%llu", &K, &n);
    if (n == 1){
        puts("1");
        return 0;
    }
    for (i = K - 1; i >= 2; i--)
        if (n%i == 0) {
            a[++m] = i;
        }
    a[0] = a[m + 1] = 1;
    dfs(1, 1, 0, n);
    if (ans == inf)
        puts("impossible");
    else
        printf("%llu", ans);
    return 0;
}
