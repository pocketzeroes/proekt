#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<limits.h>

typedef long long LL;
enum{ MOD = (int) 1e9 + 7};
int n, m;
char s[16][1005];
int d[65536], mul[65536];
int ans[17] = {};
int pc[65536];

int main() {
    for (int i = 0; i < (int)(65536); ++i) {
        pc[i] = __builtin_popcount(i);
    }
    if (0) {
        srand(time(0));
        n = 16;
        m = 1000;
        for (int i = 0; i < (int)(n); ++i) for (int j = 0; j < (int)(m); ++j) {
            s[i][j] = 'a' + rand() % 26;
            if (i & 1) {
                s[i][j] = s[i - 1][j];
            }
        }
    } 
    else {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < (int)(n); ++i) scanf("%s", s[i]);
    }
    for (int i = 0; i < (int)(1 << n); ++i) d[i] = 1;
    for (int i = 0; i < (int)(m); ++i) {
        for (int i = 0; i < (int)(1 << n); ++i) mul[i] = 1;
        int later = 0;
        for (char c = 'a'; c <= 'z'; ++c) {
            int mask = 0;
            for (int j = 0; j < (int)(n); ++j) if (s[j][i] == c) {
                mask |= 1 << j;
            }
            if (pc[mask] == 1) {
                later |= mask;
            } 
            else if (mask > 0) {
                for (int i = 0; i < (int)(1 << n); ++i) {
                    mul[i] += (1 << pc[i & mask]) - 1;
                }
            }
        }
        for (int i = 0; i < (int)(1 << n); ++i) {
            mul[i] += pc[i & later];
        }
        for (int j = 0; j < (int)(1 << n); ++j) {
            d[j] = (LL)d[j] * mul[j] % MOD;
        }
    }
    for (int i = 0; i < (int)(n); ++i) for (int j = 0; j < (int)(1 << n); ++j) if (j & (1 << i)) {
        d[j] -= d[j ^ (1 << i)];
        if (d[j] < 0) {
            d[j] += MOD;
        }
    }
    for (int i = 0; i < (int)(1 << n); ++i) {
        int cnt = __builtin_popcount(i);
        ans[cnt] += d[i];
        if (ans[cnt] >= MOD) {
            ans[cnt] -= MOD;
        }
    }
    for (int i = 0; i < (int)(n + 1); ++i) {
        printf("%d ", ans[n - i]);
    }
    puts("");
    return 0;
}





















































