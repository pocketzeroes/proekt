#include<stdio.h>

enum{ maxk = 10001};
enum{ mod  = 1000000007};
int n, k, dp[2][maxk]; 
int main(){
  scanf( "%d%d", &n, &k );
	dp[1][0] = 1;
	for( int i = 2; i <= n; i++){
		int tmp = 0;
		for( int j = 0; j <= k; j++){
			tmp = (tmp+dp[(i-1)&1][j])%mod;
			if( j >= i )
        tmp = (tmp-dp[(i-1)&1][j-i]+mod)%mod;
			dp[i&1][j] = tmp;
		}
	}
	printf( "%d\n", dp[n&1][k] );
	return 0;
}
