#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef long long ll;
typedef long double ld;

enum{ MAXN =     1000        };
enum{ MOD  =(ll) 1000000007LL};

int a[MAXN];
int cnt[MAXN];
ll dp[MAXN];
ll dp2[MAXN];
ll cnk[MAXN][MAXN];
int n;

int main(){
	for (int i = 0; i < MAXN; ++i)
		for (int j = 0; j < MAXN; ++j) {
			if (i == j || j == 0)
				cnk[i][j] = 1;
			else if (j > i)
				cnk[i][j] = 0;
			else
				cnk[i][j] = (cnk[i - 1][j - 1] + cnk[i - 1][j]) % MOD;
		}
    scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", &a[i]), --a[i], ++cnt[a[i]];
	int now = 0;
	dp[0] = 1;
	for (int it = 0; it < n; ++it) {
		if (cnt[it] == 0)
			continue;
		int cc = cnt[it];
		memset(dp2, 0, sizeof(dp2));
		for (int i = 0; i <= now; ++i) {
			for (int j = 0; j <= cc && j <= now + 1 - i; ++j) {
				for (int k = 0; j + k <= cc && k <= i; ++k) {
					if (j + k == 0)
						continue;
					int l = cc - j - k;
					ll ans = dp[i];
					ans = (ans * cnk[now + 1 - i][j]) % MOD;
					ans = (ans * cnk[i][k]) % MOD;
					ans = (ans * cnk[cc - 1][j + k - 1]) % MOD;
					dp2[i - k + l] += ans;
					if (dp2[i - k + l] >= MOD)
						dp2[i - k + l] -= MOD;
				}
			}
		}
		now += cc;
		memcpy(dp, dp2, sizeof(dp2));
	}
	printf("%lld\n", dp[0]);
	return 0;
}











