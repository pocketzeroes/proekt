#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
int max(int a,int b){return a>b?a:b;}

typedef long double ld;
typedef unsigned long long ull;
enum{ MAXN = 21000};
int a[5][120000];
int dp[MAXN * 4][5][5];
int n, m, q;
enum{ INF =(int) 1e9};

void build(int v, int tl, int tr){
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dp[v][i][j] = -INF;
    if (tl + 1 == tr) {
        for (int i = 0; i < n; ++i) {
            dp[v][i][i] = a[i][tl];
            if (i > 0)
                dp[v][i][i - 1] = a[i][tl];
            if (i + 1 < n)
                dp[v][i][i + 1] = a[i][tl];
        }
        return;
    }
    int m = (tl + tr) >> 1;
    build(v * 2 + 1, tl, m);
    build(v * 2 + 2, m, tr);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                dp[v][i][k] = max(dp[v][i][k], dp[v * 2 + 1][i][j] + dp[v * 2 + 2][j][k]);
}
void upd(int v, int tl, int tr, int x){
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dp[v][i][j] = -INF;
    if (tl + 1 == tr) {
        for (int i = 0; i < n; ++i) {
            dp[v][i][i] = a[i][tl];
            if (i > 0)
                dp[v][i][i - 1] = a[i][tl];
            if (i + 1 < n)
                dp[v][i][i + 1] = a[i][tl];
        }
        return;
    }
    int m = (tl + tr) >> 1;
    if (x < m)
        upd(v * 2 + 1, tl, m, x);
    else
        upd(v * 2 + 2, m, tr, x);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                dp[v][i][k] = max(dp[v][i][k], dp[v * 2 + 1][i][j] + dp[v * 2 + 2][j][k]);
}
int main(){
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%d", &a[i][j]);
    build(0, 0, m);
    for (int i = 0; i < q; ++i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        --x, --y;
        a[x][y] = z;
        upd(0, 0, m, y);
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                ans = max(ans, dp[0][i][j]);
        printf("%d\n", ans);
    }
    return 0;
}

