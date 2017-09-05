#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#ifdef _WIN32
  #define inline static
#endif
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

enum{ DIM =(int) 1e3 + 5};
enum{ MOD =(int) 1e9 + 7};
char mat[DIM][DIM];
int cnt[DIM][DIM], pwr[DIM * DIM];
int dp1[DIM][DIM], dp2[DIM][DIM];  
int psm1[DIM][DIM], psm2[DIM][DIM];

inline int f(int l1, int c1, int l2, int c2) {
    if (l1 > l2 || c1 > c2) return 1;
    l1 = max(l1, 1); l2 = max(l2, 1); c1 = max(c1, 1); c2 = max(c2, 1);
    return pwr[cnt[l2][c2] - cnt[l1 - 1][c2] - cnt[l2][c1 - 1] + cnt[l1 - 1][c1 - 1]];
}
int main(void) {
    int n, m, r1, r2;
    scanf("%d %d %d %d", &n, &m, &r1, &r2);
    for (int i = 1; i <= n; ++i)
        scanf("%s", mat[i] + 1);
    if (mat[r1][1] == '1' || mat[r2][m] == '1') {
        printf("%d\n", 0);
        return 0;
    }
    mat[r1][1] = mat[r2][m] = '0';
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cnt[i][j] = cnt[i - 1][j] + cnt[i][j - 1] - cnt[i - 1][j - 1] + (mat[i][j] == '?');
    pwr[0] = 1;
    for (int i = 1; i <= n * m; ++i)
        pwr[i] = (pwr[i - 1] << 1) % MOD;
    dp2[r2][m] = f(r2 + 1, m, n, m);
    dp1[r2][m] = f(1, m, n, m);
    for (int i = r2 - 1; mat[i][m] != '1' && i >= 1; --i)
        if (i == 1 || mat[i - 1][m] != '0') {
            dp2[i][m] = f(r2 + 1, m, n, m);
            dp1[i][m] = (1LL * f(1, m, i - 2, m) * f(r2 + 1, m, n, m)) % MOD;
        }
    for (int i = r2 + 1; mat[i][m] != '1' && i <= n; ++i)
        dp1[i][m] = (1LL * f(1, m, r2 - 1, m) * f(i + 1, m, n, m)) % MOD;
    for (int k = m - 1; k >= 1; --k) {
        for (int i = 1; i <= n; ++i) {
            if (mat[i][k] == '1')
                continue;
            psm1[i][k + 1] = psm1[i - 1][k + 1];
            if (mat[i][k + 1] == '1')
                continue;
            if (mat[i - 1][k] != '0' || i == 1)
                psm1[i][k + 1] = (1LL * f(1, k, i - 2, k) * dp1[i][k + 1] + psm1[i][k + 1]) % MOD;
        }
        for (int i = n; i >= 1; --i) {
            if (mat[i][k] == '1')
                continue;
            if (mat[i][k + 1] != '0')
                psm2[i][k + 1] = psm2[i + 1][k + 1];
            if (mat[i][k + 1] == '1')
                continue;
            psm2[i][k + 1] = (1LL * f(i + 1, k, n, k) * dp2[i][k + 1] + psm2[i][k + 1]) % MOD;
        }
        for (int i = 1; i <= n; ++i) {
            if (mat[i][k] == '1')
                continue;
            if (mat[i - 1][k] != '1')
                dp1[i][k] = (1LL * psm1[i - 1][k + 1] * f(i + 1, k, n, k)) % MOD;
            if (i == 1 || mat[i - 1][k] != '0') {
                dp1[i][k] = (1LL * f(i + 1, k, n, k) * f(1, k, i - 2, k) % MOD * dp1[i][k + 1] + dp1[i][k]) % MOD;
                dp2[i][k] = (1LL * f(i + 1, k, n, k) * dp1[i][k + 1]) % MOD;
            }
            if (mat[i][k + 1] != '0' && i < n && (mat[i - 1][k] != '0' || i == 1))
                dp1[i][k] = (1LL * psm2[i + 1][k + 1] * f(1, k, i - 2, k) % MOD * f(1, k + 1, i - 1, k + 1) + dp1[i][k]) % MOD;
            if (mat[i][k + 1] != '0' && i < n && mat[i + 1][k] != '1')
                dp2[i][k] = (1LL * psm2[i + 1][k + 1] * f(1, k + 1, i - 1, k + 1) + dp2[i][k]) % MOD;
        }
    }
    printf("%d\n", dp1[r1][1]);
    return 0;
}





























