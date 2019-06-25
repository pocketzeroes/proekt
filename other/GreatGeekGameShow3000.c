#include<stdio.h>

double dp[10000001];

int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	for(int i = 0; i <= k; ++i)
		dp[i] = 1.0;
	double sum = k;
	for(int i = k+1; i <= n; ++i)
		sum += (dp[i] = sum/i) - dp[i-k];
	printf("%lf\n", dp[n]);
	return 0;
}
