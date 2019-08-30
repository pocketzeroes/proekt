#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ INF = (int)1E9};

int N, K;
int dp[205][205][4];
int main(){
    while (1){
        scanf("%d%d", &N, &K);
        if (N == 0 && K == 0) 
            break;
        for(int i=(0);i<(N+1);i++) for(int j=(0);j<(K+1);j++) for(int t=(0);t<(4);t++) dp[i][j][t] = INF;
        dp[0][0][0] = 0;
        int sum = 0;
        for(int i=(1);i<(N + 1);i++){
            int a, b;
            scanf("%d%d", &a, &b);
            sum += a + b;
            for(int k=(0);k<(K + 1);k++){
                for(int t=(0);t<(4);t++){
                    dp[i][k][0] = fmin(dp[i][k][0], dp[i - 1][k][t]);
                    int cnt = ((t & 1) == 1) + ((t & 2) == 2);
                    if (k + cnt > K) continue;
                    int val = 0;
                    if (t & 1) val += a;
                    if (t & 2) val += b;
                    for(int pt=(0);pt<(4);pt++){
                        int nt = t | pt;
                        if (nt == 3) continue;
                        dp[i][k + cnt][nt] = fmin(dp[i][k + cnt][nt], dp[i - 1][k][pt] + val);
                    }
                }
            }
        }
        int ans = INF;
        for(int t=(0);t<(4);t++) ans = fmin(ans, dp[N][K][t]);
        printf("%d\n", sum-ans);
    }
    return 0;
}
