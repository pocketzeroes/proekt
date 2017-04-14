#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef long long int64;

int64 min(int64 a,int64 b){return a<b?a:b;}
int64 max(int64 a,int64 b){return a>b?a:b;}


enum{ kMaxN   =(int) 750       };
enum{ inf     =(int) 0x3f3f3f3f};
enum{ kMaxVal =(int) 1e5       };

int cmp (const void * a, const void * b)
{
   return ( *(int*)a < *(int*)b );
}

int main() {
    int n;
    scanf("%d", &n);
    int   num_cnt[n];
    int64 right_sum[n + 1];
    memset(right_sum,0,sizeof(right_sum));
    for (int i = 0; i < n; i += 1) {
        scanf("%d", &num_cnt[i]);
    }
    qsort(num_cnt, n, sizeof(int), cmp);//reverse
//  reverse(num_cnt, 0, n-1);
    for (int i = n - 1; i >= 0; i -= 1) {
        right_sum[i] = right_sum[i + 1] + num_cnt[i];
    }
    int sz=n+1;
    int64 dp[sz][sz];
    for(int i=0;i<sz;i++)
        for(int j=0;j<sz;j++)
            dp[i][j]=1LL*inf*inf;
    dp[1][1] = right_sum[0];
    for (int solved = 0; solved < n; solved += 1) {
        for (int small = 0; solved + small <= n; small += 1) {
            for (int big = 0; solved + small + big <= n; big += 1) {
                int new_small = big + small;
                int new_big = small;
                dp[new_small][new_big] = min(dp[new_small][new_big], dp[small][big] + right_sum[solved]);
            }
        }
        for (int small = 1; small <= n - solved; small += 1) {
            for (int big = 0; big <= n - solved; big += 1) {
                dp[small - 1][big] = dp[small][big];
            }
        }
        for (int small = 0; small < n - solved; small += 1) {
            dp[small][n - solved - 1] = min(dp[small][n - solved - 1], dp[small][n - solved]);
        }
    }
    printf("%lld\n", dp[0][0] );
    return 0;
}



























