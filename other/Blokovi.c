#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int N;
    scanf("%d",&N);
    int m[N];
    for(int i = 0;i < N;++i)
        scanf("%d",&m[i]);
    long long M = m[N - 1];
    double dp[N];
    dp[N - 1] = 1;
    for(int i = N - 2;i > 0;--i){
        M += m[i];
        dp[i] = fmax(fmax(dp[i + 1],2.0) - (double)m[i] / M,dp[i + 1] + (double)m[i] / M);
    }
    printf("%.8f\n",dp[1]);
    return 0;
}
