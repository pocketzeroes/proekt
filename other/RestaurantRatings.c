#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ maxn = 35};
ll dp[maxn][maxn] = {1},ret;
int d[maxn],n,sum;

int main(){
    for(int i = 1; i < 16; ++i){
        for(int j = 0; j <= 30; ++j)
            for(int k = 0; k <= j; ++k)
                dp[i][j] += dp[i-1][j - k];
    }
    while(scanf("%d",&n),n){
        for(int i = sum = 0; i < n; ++i){
            scanf("%d",d+i);
            sum += d[i];
        }
        ret = 1;
        for(int i = 0; i < sum; ++i)
            ret += dp[n][i];
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < d[i]; ++j)
                ret += dp[n-i-1][sum - j];
            sum -= d[i];
        }
        printf("%lld\n",ret);
    }
    return 0;
}
