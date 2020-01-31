#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char str[1001];
int dp[1001][1001];
long long strhash[1001];
long long M = 1000000007;
long long p[1001];

long long getHash(int l, int r){
    l++; r++;
    return (strhash[r] - (strhash[l - 1] * p[r - l + 1]) % M + M) % M;
}
int getKey(char ch){
    if (ch >= 'a' && ch <= 'z') return ch - 'a' + 1;
    if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 27;
    return ch - '0' + 54;
}
int solve(int l, int r){
    if (~dp[l][r]) 
        return dp[l][r];
    if (l == r) {
        dp[l][r] == 1;
        return 1;
    }
    int ans = 99999999;
    for (int i = 1; i <= r - l; ++i){
        int j;
        long long rep = getHash(l, l + i - 1);
        for (j = l; j <= r - i + 1; j += i) if (rep != getHash(j, j + i - 1)) break;
        int f1, f2;
        f1 = f2 = 0;
        f1 = solve(l, l + i - 1);
        if (j <= r) f2 = solve(j, r);
        ans = fmin(ans, f1 + f2);
    }
    dp[l][r] = ans;
    return ans;
}
int main(){
    int len;
    scanf("%d", &len);
    scanf("%s", str);
    p[0] = 1;
    for (int i = 1; i <= len; ++i) p[i] = p[i - 1] * 71 % M;
    strhash[0] = 0;
    for (int i = 1; i <= len; ++i) strhash[i] = ((strhash[i - 1] * 71) % M + getKey(str[i - 1])) % M;
    memset(dp, -1, sizeof(dp));
    printf("%d\n", solve(0, len - 1));
    return 0;
}
