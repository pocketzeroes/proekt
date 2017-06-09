#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
typedef long long LL;

enum{ MOD  =(int) 1e9 + 7};
enum{ MAXN =(int) 4100   };

int dp[MAXN][MAXN];
int sum[MAXN];

int modExp(int a, int n, int p) {
	int ret = 1;
	for (; n; n >>= 1, a = (LL)a * a % p) 
        if (n & 1) 
            ret = (LL)ret * a % p;
	return ret;
}
int main() {
	int N, K, M; 
    scanf("%d%d%d", &N, &K, &M);
	dp[0][0] = sum[0] = 1;
	for (int i = 1; i <= K; i++) {
		for (int j = i; j <= N; j++) 
            dp[i][j] = sum[j-i], sum[j] = (sum[j] + dp[i][j]) % MOD;
	}
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		int cur = modExp(i, M, MOD), sum = 0;
		for (int j = 1; j <= N/i && j <= K; j++) {
			sum = (sum + dp[K-j][N-j*i]) % MOD;
		}
		ans = (ans + 1LL * sum * cur) % MOD;
	}
	printf("%d\n", ans);
	return 0;
}


















































