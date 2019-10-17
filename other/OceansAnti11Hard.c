#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN = 10004    };
enum{ MAXB = 12       };
enum{ MOD  =(int)1e9+7};
int n;
char b[MAXB];
int bits;
int dp[2][1 << MAXB];

int solve(int bad){
    if (n < bits)
        return 1 << n;
    int cap = (1 << bits);
    for (int mask = 0; mask < cap; ++mask)
        dp[0][mask] = 1;
    dp[0][bad] = 0;
    for (int i = bits; i < n; ++i){
        for (int mask = 0; mask < cap; ++mask){
            int newmask = (mask << 1) & (cap - 1);
            for (int k = 0; k < 2; ++k){
                dp[1][newmask | k] += dp[0][mask];
                if (dp[1][newmask | k] >= MOD)
                    dp[1][newmask | k] -= MOD;
            }
        }
        for (int mask = 0; mask < cap; ++mask){
            dp[0][mask] = dp[1][mask];
            dp[1][mask] = 0;
        }
        dp[0][bad] = 0;
    }
    int res = 0;
    for (int mask = 0; mask < cap; ++mask){
        res += dp[0][mask];
        if (res >= MOD)
            res -= MOD;
    }
    return res;
}
int main(){
    int T;
    scanf("%d", &T);
    while (T-- > 0){
        scanf("%d %s", &n, b);
        bits = strlen(b);
        int x = 0;
        for (int i = 0; i < bits; ++i){
            x <<= 1;
            x |= (b[i] == '1');
        }
        printf("%d\n", solve(x));
    }
    return 0;
}
