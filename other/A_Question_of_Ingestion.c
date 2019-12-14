#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int n;
int pow_list[200];
int lim     [200];
int dp [200][200][3];

int main(){
    scanf("%d %d", &n, &pow_list[0]);
    for(int i = 0; i < n; ++i)
        pow_list[i + 1] = (int)(pow_list[i] * 2. / 3);
    for(int i = 0; i < n; ++i)
        scanf("%d", &lim[i]);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= n; ++j){
            dp[i][j][0] = -(1 << 30);
            dp[i][j][1] = -(1 << 30);
            dp[i][j][2] = -(1 << 30);
        }
    dp[0][0][2] = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j <= n; ++j){
            int w1 = fmin(pow_list[j], lim[i]);
            if(dp[i + 1][j + 1][0] < dp[i][j][0] + w1)
               dp[i + 1][j + 1][0] = dp[i][j][0] + w1;
            if(dp[i + 1][j][1] < dp[i][j][0])
               dp[i + 1][j][1] = dp[i][j][0];
            int w2 = fmin(pow_list[(int)fmax(j-1, 0)], lim[i]);
            if(dp[i + 1][j][0] < dp[i][j][1] + w2)
               dp[i + 1][j][0] = dp[i][j][1] + w2;
            if(dp[i + 1][j][2] < dp[i][j][1])
               dp[i + 1][j][2] = dp[i][j][1];
            int w3 = fmin(pow_list[0], lim[i]);
            if(dp[i + 1][1][0] < dp[i][j][2] + w3)
               dp[i + 1][1][0] = dp[i][j][2] + w3;
            if(dp[i + 1][j][2] < dp[i][j][2])
               dp[i + 1][j][2] = dp[i][j][2];
        }
    }
    int best = 0;
    for(int j = 0; j <= n; ++j){
        if(best < dp[n][j][0])
           best = dp[n][j][0];
        if(best < dp[n][j][1])
           best = dp[n][j][1];
        if(best < dp[n][j][2])
           best = dp[n][j][2];
    }
    printf("%d\n", best);
    return 0;
}
