#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

double c[1005][1005], f[2][505][505], g[2][505][505];

int main(){
    for(int i = 0; i < 1005; ++i) c[i][0] = c[i][i] = 1;
    for(int i = 2; i < 1005; ++i)
        for(int j = 1; j < i; ++j)
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    double ans = 0;
    int n, d, r, o = 0;
    scanf("%d %d %d", &n, &d, &r);
    f[0][0][n] = r, g[0][0][n] = 1;
    for(int i = 2; i <= d + 1; ++i) {
        o ^= 1;
        memset(f[o], 0, sizeof(f[o]));
        memset(g[o], 0, sizeof(g[o]));
        for(int j = 0; j <= d; ++j) {
            for(int k = 1; k <= n; ++k) {
                if(g[o ^ 1][j][k] == 0) continue;
                for(int l = 1; l <= k; ++l) {
                    if(j + l > d) break;
                    g[o][j + l][l] += g[o ^ 1][j][k] * c[k][l];
                    f[o][j + l][l] += f[o ^ 1][j][k] * c[k][l] + g[o ^ 1][j][k] * c[k][l] * fmin(l, r);
                }
            }
        }
        for(int k = 1; k <= n; ++k) ans += f[o][d][k];
    }
    printf("%.8f\n", ans / c[d + n - 1][d]);
    return 0;
}
