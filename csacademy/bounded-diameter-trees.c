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


enum{ MAX_N = 300     };
enum{ MAX_P = (int)1e9};
int n, m, p;
long long dp [MAX_N + 1][MAX_N + 1];
long long sum[MAX_N + 1][MAX_N + 1];
inline void add(long long*a, long long b) {
    *a = (*a + b) % p;
}
int main() {
    scanf("%d %d %d", &n, &m, &p);
    sum[1][0] = dp[1][0] = 1;
    for (int j = 1; j <= m; ++j) {
        sum[1][j] = 1;
    }
    for (int i = 2; i <= n; ++i) { 
        for (int j = 1; j <= m; ++j) { 
            add(&dp[i][j], dp[i-1][j-1]);
            for (int k = 1; k <= i - 2; ++k) {
                add(&dp[i][j], dp[k][j - 1] * sum[i - k][min(j, m - j)]);
            }
            for (int k = 1; k <= i - 2; ++k) {
                add(&dp[i][j], sum[k][min(j - 2, m - j - 1)] * dp[i - k][j]);
            }
            sum[i][j] = sum[i][j - 1];
            add(&sum[i][j], dp[i][j]);
        }
    }
    printf("%lld\n", sum[n][m]);
}

































