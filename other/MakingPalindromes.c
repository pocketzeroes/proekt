#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{ MAXN = 404};
enum{ MOD =(int)1e9 + 7};
int n;
char s[MAXN];
int dp[MAXN][MAXN][MAXN];

int sum(int a, int b){
    int c = a + b;
    if (c >= MOD)
        c -= MOD;
    return c;
}
int prod(int a, int b){
    return 1LL * a * b % MOD;
}
int modpow(int base, int exp){
    int res = 1;
    int cur = base;
    for (int p = 1; p <= exp; p <<= 1){
        if (exp & p)
            res = prod(res, cur);
        cur = prod(cur, cur);
    }
    return res;
}
int solve(int len, int pref, int suff){
    if (pref > suff)
        return modpow(26, n - len);
    if (len == n)
        return 0;
#define res dp[len][pref][suff]
    if (res != -1)
        return res;
    res = 0;
    for (char c = 'A'; c <= 'Z'; ++c) {
        int np = c == s[pref] ? pref + 1 : pref;
        int ns = c == s[suff] ? suff - 1 : suff;
        res = sum(res, solve(len + 1, np, ns));
    }
    return res;
    #undef res
}
int main() {
    scanf(" %d", &n);
    scanf(" %s", s);
    memset(dp, -1, sizeof(dp));
    printf("%d\n", solve(0, 0, n - 1));
    return 0;
}
