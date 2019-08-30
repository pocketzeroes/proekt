#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN = 505};
enum{ MAXM = 20};
enum{ MOD = 10000};
char pattern[] = "welcome to code jam";
int n;
char s[MAXN];
int dp[MAXN][MAXM];
int main() {
    int m = strlen(pattern);
    int T;
    scanf("%d\n", &T);
    int tc = 1;
    while(T-- > 0){
        gets(s);
        n = strlen(s);
        memset(dp, 0, sizeof(dp));
        if (s[0] == 'w')
            dp[0][0] = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                dp[i][j] = dp[i - 1][j];
                if (s[i] == pattern[j]) {
                    dp[i][j] += j ? dp[i - 1][j - 1] : 1;
                    dp[i][j] %= MOD;
                }
            }
        }
        int ans = dp[n - 1][m - 1];
        printf("Case #%d: %04d\n", tc++, ans);
    }
    return 0;
}
