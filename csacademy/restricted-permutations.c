#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>


#define eps 0.00000001
#define LONG_INF 10000000000000000
#define GOLD 1.61803398874989484820458
#define MAX_MOD 1000000007
#define f(n) for(int i=0;i<n;++i)
#define REP(i,n) for(long long i = 0;i < n;++i)
long long dp[3000] = {};

int main() {
	int n;
	scanf("%d", &n);
	dp[0] = 1;
	REP(i, n-1) {
		int a;
		scanf("%d", &a);
		if (a == 0) {
			long long hoge = 0;
			for (int q = 0;q <= i+1;++q) {
				long long geko = hoge;
				hoge += dp[q];
				hoge %= MAX_MOD;
				dp[q] = geko;
			}
		}
        else{
			long long hoge = 0;
			for (int q = i;q >= 0;--q) {
				hoge += dp[q];
				hoge %= MAX_MOD;
				dp[q] = hoge;
			}
		}
	}
	long long ans = 0;
	for (int i = 0;i <= n;++i) {
		ans += dp[i];
		ans %= MAX_MOD;
	}
	printf("%lld\n", ans);
	return 0;
}
