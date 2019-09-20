#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN = 305};
enum{ INF = 0x3f3f3f3f};
int dp[MAXN][MAXN], nCase, m, S, value[2][45], ans;

void input(){
    scanf("%d%d", &m, &S);
    for(int i = 0; i < m; i++)
        scanf("%d%d", &value[0][i], &value[1][i]);
}
void work(){
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < m; i++)
        for (int u = value[0][i]; u <= S; u++)
            for (int v = value[1][i]; v <= S; v++)
                dp[u][v] = fmin(dp[u][v], dp[u-value[0][i]][v-value[1][i]] + 1);
}
void findAns(){
    ans = INF;
    for (int i = 0; i <= S; i++)
        for (int j = 0; j <= S; j++)
            if (i*i + j*j == S*S && dp[i][j])
                ans = fmin(ans, dp[i][j]);
}
void output() {
    if (ans != INF)
        printf("%d\n", ans);
    else
        puts("not possible");
}
int main() {
    scanf("%d", &nCase);
    while(nCase--){
        input();
        work();
        findAns();
        output();
    }
    return 0;
}
