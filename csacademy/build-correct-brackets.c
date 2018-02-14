#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}



enum{ N = 2600};
int dp [2][N];
int cnt[2][N];
enum{ INF = 0x3f3f3f3f };
enum{ MOD =(int) 1e9 + 7};
char s[100000];
void add(int*a, int b){
    (*a) += b;
    if (*a >= MOD)
        *a -= MOD;
}
int main(){
    while(scanf("%s", &s)==1){
        int n = strlen(s);
        int cur = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < N; j++) {
                dp[i][j] = INF;
            }
        }
        dp [cur][0] = 0;
        cnt[cur][0] = 1;
        for (int i = 0; i < n; i++, cur ^= 1) {
            int left = s[i] == '(';
            for (int j = 0; j <= n / 2; j++) {
                int foo = INF, fooCnt = 0;
                int bar = INF, barCnt = 0;
                if (left) {
                    if (j > 0) {
                        foo = dp[cur][j - 1];
                        fooCnt = cnt[cur][j - 1];
                    }
                    bar = min(bar, dp[cur][j + 1] + 1);
                    barCnt = cnt[cur][j + 1];
                    dp[cur ^ 1][j] = min(foo, bar);
                    cnt[cur ^ 1][j] = 0;
                    if (dp[cur ^ 1][j] == foo) add(&cnt[cur ^ 1][j], fooCnt);
                    if (dp[cur ^ 1][j] == bar) add(&cnt[cur ^ 1][j], barCnt);
                }
                else {
                    if (j > 0) {
                        foo = dp[cur][j - 1] + 1;
                        fooCnt = cnt[cur][j - 1];
                    }
                    bar = min(bar, dp[cur][j + 1]);
                    barCnt = cnt[cur][j + 1];
                    dp[cur ^ 1][j] = min(foo, bar);
                    cnt[cur ^ 1][j] = 0;
                    if (dp[cur ^ 1][j] == foo) add(&cnt[cur ^ 1][j], fooCnt);
                    if (dp[cur ^ 1][j] == bar) add(&cnt[cur ^ 1][j], barCnt);
                }
            } 
        }
        printf("%d %d\n", dp[cur][0] , cnt[cur][0] );
    }
    return 0;
}
