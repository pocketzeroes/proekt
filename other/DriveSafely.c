#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<float.h>

typedef long double ld;

enum{ INF =(int) 1e9};
enum{ MAXN = 210};
enum{ MAXK = 55 };

const ld EPS = 1e-9;

ld dp[MAXN][MAXK][2];

inline void upd(ld*a, ld b){
    *a = fminl(*a, b);
}
int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    ld x[n];
    ld y[n];
    for(int i=0; i<n; ++i)
        scanf("%Lf %Lf", &x[i], &y[i]);
    ld a  [n  ];
    ld len[n-1];
    a[0] = 180;
    for(int i=0; i<n-2; ++i){
        ld px = x[i + 1] - x[i], py = y[i + 1] - y[i];
        ld nx = x[i + 2] - x[i + 1], ny = y[i + 2] - y[i + 1];
        a[i + 1] = 180 - fabsl(atan2(px * ny - nx * py, px * nx + py * ny)) / M_PI * 180;
    }
    a[n - 1] = 0;
    for(int i=0; i<n-1; ++i){
        ld px = x[i + 1] - x[i],
           py = y[i + 1] - y[i];
        len[i] = sqrt(px * px + py * py);
    }
    for(int last = 0; last < n - 1; ++last)
        for (int used = 0; used <= k; ++used)
            for(int i = 0; i < 2; ++i)
                dp[last][used][i] = LDBL_MAX;
    dp[0][0][0] = 0;
    dp[0][0][1] = len[0] / 180;
    for(int last = 1; last < n - 1; ++last){
        if(a[last] < 180 - EPS)
            break;
        dp[last][0][0] = dp[last - 1][0][1];
        dp[last][0][1] = dp[last][0][0] + len[last] / 180;
    }
    for(int last = 1; last < n - 1; ++last){
        for (int used = 1; used <= k; ++used){
            ld minSpeed = 180;
            ld totalDist = 0;
            for(int corner = last; corner > 0; --corner){
                minSpeed = fminl(minSpeed, a[corner]);
                totalDist += len[corner];
                upd(&dp[last][used][1], dp[corner - 1][used - 1][1] + totalDist / minSpeed);
                upd(&dp[last][used][0], dp[corner - 1][used - 1][1] + (totalDist - len[last]) / minSpeed);
                upd(&dp[last][used][1], dp[corner - 1][used - 1][0] + (totalDist + len[corner - 1]) / minSpeed);
                upd(&dp[last][used][0], dp[corner - 1][used - 1][0] + (totalDist - len[last] + len[corner - 1]) / minSpeed);
            }
            upd(&dp[last][used][1], dp[last][used - 1][0] + len[last] / 180);
        }
    }
    ld ans = LDBL_MAX;
    for(int used=0; used<=k; ++used)
        upd(&ans, dp[n - 2][used][1]);
    printf("%.20Lf\n", ans);
    return 0;
}
