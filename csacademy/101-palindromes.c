#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

typedef long long ll;
typedef long double ld;

enum{ MAXN =(int) 205    };
enum{ MOD  =(int) 1e9 + 7};
int dp[MAXN][MAXN][101][4];
int n;
char s[500];
int a[MAXN];
int cc[4] = {11, 0, 92, 2};

int nm(int a) {
	return (a >= MOD ? a - MOD : (a < 0 ? a + MOD : a));
}
int main() {
    scanf("%d %s", &n, &s);
	for (int i = 0; i < n; ++i)
		a[i] = s[i] - '0';
	for (int i = n - 1; i >= 0; --i) {
		for (int j = i; j < n; ++j) {
			if (i == j) {
				dp[i][j][a[i]][1] = 1;
				continue;
			}
			if (i + 1 == j) {
				dp[i][j][a[i]][1] += 1;
				dp[i][j][a[j]][1] += 1;
				if (a[i] == a[j])
					dp[i][j][a[i] * 10 + a[j]][2] += 1;
				continue;
			}
			for (int k = 0; k < 101; ++k)
				for (int t = 0; t < 4; ++t)
					dp[i][j][k][t] = nm(dp[i][j - 1][k][t] + dp[i + 1][j][k][t] - dp[i + 1][j - 1][k][t]);
			if (a[i] == a[j]) {
				for (int k = 0; k < 101; ++k) {
					for (int t = 0; t < 4; ++t)
						dp[i][j][(k * 10 + (cc[t] * a[i])) % 101][(t + 2) & 3] = nm(dp[i][j][(k * 10 + (cc[t] * a[i])) % 101][(t + 2) & 3] + dp[i + 1][j - 1][k][t]);
				}
				dp[i][j][a[i] * 11][2] = nm(dp[i][j][a[i] * 11][2] + 1);
			}
		}
	}
	ll ans = 0;
	for (int i = 0; i < 4; ++i)
		ans += dp[0][n - 1][0][i];
    printf("%lld\n", ans%MOD);
	return 0;
}



























































