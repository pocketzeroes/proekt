#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
        
#define maxN 3011
#define mod 1000000007

int t, ti;
int n, m, k, s;
int i, j;
int ss, dd, id;
int dp[2][maxN];
int cnt1[maxN], cnt2[maxN];

void add(int*a, int b) {
   *a += b;
    if (*a >= mod) 
        *a -= mod;
}
int compute(int limit) {
    int i, j;
    ss = 0; dd = 1;
    memset(dp, 0, sizeof(dp));
    dp[ss][0] = 1;
    for (i = 1; i <= k; i++) {
        for (j = 0; j <= limit; j++)
            dp[dd][j] = 0;
        for (j = 0; j <= limit; j++) {
            if (dp[ss][j] == 0) 
                continue;
            add(&dp[dd][j + 1], (1LL * dp[ss][j] * (limit - j)) % mod);
            if (j > 0) 
                add(&dp[dd][j - 1], (1LL * dp[ss][j] * j) % mod);
        }
        swap(ss, dd);
    }
    id = ss;
}
int solve() {
    int i, j, act;
    int ans = 0;
    compute(n);
    for (i = 0; i <= n; i++) cnt1[i] = dp[ss][i];
    compute(m);
    for (i = 0; i <= m; i++) cnt2[i] = dp[ss][i];
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= m; j++) {
            act = n * m - i * j - (n - i) * (m - j);
            if (act == s) {
                add(&ans, (1LL * cnt1[i] * cnt2[j]) % mod);
            }
        }
    }
    return ans;
}
int main(){
    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++){
        scanf("%d %d %d %d", &n, &m, &k, &s);
        printf("%d\n", solve() );
    }
    return 0;
}


































