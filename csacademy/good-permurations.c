#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
typedef long long ll;

enum{ N = 17};
int n, q;
int dp[1 << N];
ll d[1 << N];
char buf[N + 5];

int main() {
    scanf("%d%d", &n, &q);
    forn(i, q) {
        int mask = 0;
        scanf("%s", buf);
        forn(j, n) if (buf[j] == '1') {
            mask |= 1 << j;
        }
        ++dp[mask];
    }
    forn(j, n) forn(mask, 1 << n) if (mask & (1 << j)) {
        dp[mask] += dp[mask ^ (1 << j)];
    }
    forn(i, n) d[1 << i] = dp[1 << i] & 1;
    for (int mask = 1; mask < (1 << n); ++mask) if (d[mask]) {
        forn(j, n) if (!(mask & (1 << j)) && !((dp[mask | (1 << j)] - dp[mask]) & 1)) {
            d[mask ^ (1 << j)] += d[mask];
        }
    }
    printf("%lld\n", d[(1 << n) - 1] );
    return 0;
}
