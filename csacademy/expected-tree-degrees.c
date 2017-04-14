#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef long long ll;
typedef long double ld;

enum{ MX = 90};

ld dp[MX];
int n;
int main() {
	scanf("%d", &n);
	dp[1] = 1;
	ld ans = 0;
	for (int i = n - 1; i > 0; --i) {
		for (int j = 1; j < MX; ++j)
			ans += j * j * dp[j];
		if (i == 1) {
			for (int j = 1; j < MX; ++j)
				ans += j * j * dp[j];
		}
		for (int j = MX - 1; j >= 1; --j)
			dp[j] = (dp[j - 1] + (i - 1) * dp[j]) / i;
	}
	printf("%llf", ans);
	return 0;
}


