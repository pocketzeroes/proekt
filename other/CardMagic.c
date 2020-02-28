#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define DEBUG(x) cout << '>' << #x << ':' << x << endl;
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
typedef long long ll;
typedef unsigned long long ull;
enum{ M = 1000000009};

int main(){
    int n, k, t, dp[5001] = {};
    scanf("%d %d %d", &n, &k, &t);
    dp[0] = 1;
    REP(i, n){
    	FORD(j, i*k, i){
    		FOR(l, 1, k){
    			dp[j+l] = (dp[j+l]+dp[j]) % M;
    		}
    		dp[j] = 0;
    	}
    }
    printf("%d\n", dp[t]);
    return 0;
}
