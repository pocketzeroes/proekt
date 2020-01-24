#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN = 21};
const double INF = 1e18;
int n;
double dp[1 << MAXN];
double xs[MAXN], ys[MAXN];

static inline double dist(const double x1, const double y1, const double x2, const double y2){
    const double xd = x1 - x2;
    const double yd = y1 - y2;
    return sqrt(xd * xd + yd * yd);
}
int main(){
    double x, y;
    scanf("%lf %lf", &x, &y);
    scanf("%d", &n);
    for(int i=0; i<n; ++i){
        scanf("%lf %lf", &xs[i], &ys[i]);
        dp[1 << i] = 2 * dist(x, y, xs[i], ys[i]);
    }
    for(int mask=1; mask<(1<<n); ++mask){
        if(__builtin_popcount(mask)==1)
            continue;
        dp[mask] = INF;
        for(int i=0; i<n; ++i){
            if((mask&(1<<i))==0)
                continue;
            dp[mask] = fmin(dp[mask], dp[mask ^ (1 << i)] + 2.0 * dist(x, y, xs[i], ys[i]));
            for(int j = 0; j < n; ++j) {
                if(i == j || (mask & (1 << j)) == 0)
                    continue;
                dp[mask] = fmin(dp[mask], dp[mask ^ (1 << i) ^ (1 << j)] + dist(x, y, xs[i], ys[i]) + dist(xs[i], ys[i], xs[j], ys[j]) + dist(xs[j], ys[j], x, y));
            }
        }
    }
    int all = (1 << n) - 1;
    double ans = INF;
    for(int i=0; i<n; ++i)
        ans = fmin(ans, dp[all] - dist(x, y, xs[i], ys[i]));
    printf("%.9f\n", ans);
    return 0;
}
