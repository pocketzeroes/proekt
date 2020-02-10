#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ N =(int)1e6 + 5, MOD =(int)1e9 + 7};
int f[N * 2], b[N], _l[N], _r[N], n;

int fat(int x){
    if (x == f[x])
        return x;
    return f[x] = fat(f[x]);
}
void join(int x, int xi, int y, int yi){
    x = x * 2 + xi;
    y = y * 2 + yi;
    f[fat(x)] = fat(y);
}
char s[N];

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i)
        scanf("%d%d%d", &_l[i], &_r[i], &b[i]);
    int ans = 0;
    for (int all = 0; all <= 1; ++ all){
        for (int i = 0; i < 2 * (n + 1); ++ i)
            f[i] = i;
        for (int i = 0; i < n; ++ i){
            int eq = b[i], 
                l = i - _l[i], 
                r = i + _r[i];
            if (l < 0){
                r = i - _l[i] + n - 1;
                l = i + _r[i] + 1;
                eq ^= all;
            }
            else if (r >= n){
                r = i - _l[i] - 1;
                l = i + _r[i] - n + 1;
                eq ^= all;
            }
            join(l, 0, r + 1, eq);
            join(l, 1, r + 1, eq ^ 1);
        }
        bool gg = 0;
        for (int i = 0; i <= n; ++ i){
            if (fat(i * 2) == fat(i * 2 + 1))
                gg = 1;
        }
        if (fat(0) == fat(n * 2 + (all ^ 1)))
            gg = 1;
        if (gg)
            continue;
        int res = 1;
        for (int i = 0; i <= n; ++ i){
            if (f[i * 2] == i * 2){
                if (fat(0) == fat(i * 2) || fat(n * 2 + all) == fat(i * 2)) 
                    continue;
                if (fat(0) == fat(i * 2 + 1) || fat(n * 2 + all) == fat(i * 2 + 1)) 
                    continue;
                res *= 2;
                res %= MOD;
            }
        }
        ans += res;
        ans %= MOD;
    }
    printf("%d\n", ans);
    return 0;
}
