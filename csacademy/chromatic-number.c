#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

enum{ N = 310};
int n, m, k;
ll d  [N][N];
ll cnt[N][N];
ll dp1[N][N];
ll dp2[N][N];
enum{ mod =(ll) 1e9 + 7};



void load(){
    scanf("%d %d %d",&n,&m,&k);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)
                d[i][j] = 1e18;
    for (int i = 0, a, b, c; i < m; i++){
        scanf("%d %d %d",&a,&b,&c);
        d[a][b] = d[b][a] = c;
        cnt[a][b] = cnt[b][a] = 1;
    }
}
void floyd(){
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                if (d[i][j] > d[i][k] + d[k][j]) {
                    cnt[i][j] = 0;
                    d[i][j] = d[i][k] + d[k][j];
                }
                if (d[i][j] == d[i][k] + d[k][j]) {
                    cnt[i][j] += cnt[i][k] * cnt[k][j];
                }
            }
}
ll foo1(int k, int v){
    if (dp1[k][v] != -1)
        return dp1[k][v];
#define res dp1[k][v]
    if (k == 0)
        return res = cnt[v][n];
    if (k == 1 && v == n)
        return res = 1;
    res = 0;
    for (int u = 1; u <= n; u++)
        if (u != v && d[v][u] + d[u][n] == d[v][n])
            res = max(cnt[v][u] * foo1(k-1, u), res);
    if (v == 1) {
        for (int u = 2; u <= n; u++)
            if (d[v][u] + d[u][n] == d[v][n])
                res = max(res, cnt[v][u] * foo1(k, u));
    }
    return res;
#undef res
}
ll foo2(int k, int v){
#define res dp2[k][v]
    if (res != -1)
        return res;
    if (k == 0)
        return res = 1;
    if (k == 1 && v == n)
        return res = 1;
    res = 0;
    for (int u = 1; u <= n; u++)
        if (u != v && d[v][u] + d[u][n] == d[v][n] && dp1[k][v] == cnt[v][u] * dp1[k-1][u] && (k > 1 || u == n)) {
            res = (res + foo2(k-1, u)) % mod;
        }
    if (v == 1) {
        for (int u = 2; u <= n; u++)
            if (d[v][u] + d[u][n] == d[v][n] && dp1[k][v] == cnt[v][u] * dp1[k][u])
                res = (res + foo2(k, u)) % mod;
    }
    return res;
#undef res
}
int main(){
    load();
    floyd();
    memset(dp1, 0xff, sizeof(dp1));
    memset(dp2, 0xff, sizeof(dp2));
    for (int i = 1; i <= n; i++)
        cnt[i][i] = 1;
    ll res1 = foo1(k, 1);
    printf("%lld %lld\n", res1, foo2(k, 1));
    return 0;
}






















































