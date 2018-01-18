#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) (((a)>(b))?(a):(b))

typedef long long ll;

enum{ N = (int)1e4 + 5};
char ans[2 * N];
ll U[N], V[N];



ll getA(int x, int y) {
    return - ((U[x - 1] + y) ^ (V[y - 1] + x));
}
void solve(int x1, int y1, int x2, int y2, int ansL, int ansR){
    if (x1 == x2) {
        for (int i = ansL; i < ansR; i++)
            ans[i] = 'R';
        return;
    }
    if (x1 + 1 == x2) {
        ll curSum = 0;
        ll bstSum = -1;
        int bst = -1;
        for (int y = y1; y <= y2; y++)
            curSum += getA(x2, y);
        bstSum = curSum;
        bst = y1;
        for (int y = y1 + 1; y <= y2; y++) {
            curSum += getA(x1, y) - getA(x2, y - 1);
            if (curSum > bstSum) {
                bstSum = curSum;
                bst = y;
            }
        }
        for (int i = y1; i < bst; i++)
            ans[ansL++] = 'R';
        ans[ansL++] = 'D';
        for (int i = bst; i < y2; i++)
            ans[ansL++] = 'R';
        return;
    }
    int x3 = (x1 + x2) / 2;
    ll dp[max(x3 - x1, x2 - x3) + 1];
    ll A[y2 - y1 + 1];
    dp[0] = 0;
    for (int i = x1 + 1; i <= x3; i++) {
        dp[i - x1] = dp[i - x1 - 1] + getA(i, y1);
    }
    A[0] = dp[x3 - x1];
    for (int y = y1 + 1; y <= y2; y++) {
        dp[0] += getA(x1, y);
        for (int i = 1; i <= x3 - x1; i++)
            dp[i] = max(dp[i], dp[i - 1]) + getA(x1 + i, y);
        A[y - y1] = dp[x3 - x1];
    }
    dp[0] = 0;
    for (int i = x2 - 1; i >= x3; i--) {
        dp[x2 - i] = dp[x2 - i - 1] + getA(i, y2);
    }
    A[y2 - y1] += dp[x2 - x3];
    for (int y = y2 - 1; y >= y1; y--) {
        dp[0] += getA(x2, y);
        for (int i = 1; i <= x2 - x3; i++)
            dp[i] = max(dp[i], dp[i - 1]) + getA(x2 - i, y);
        A[y - y1] += dp[x2 - x3];
    }
    int bst = y1;
    for (int y = y1; y <= y2; y++) {
        A[y - y1] -= getA(x3, y);
        if (A[y - y1] > A[bst - y1])
            bst = y;
    }
    int ansM = ansL + x3 - x1 + bst - y1;
    solve(x1, y1, x3, bst, ansL, ansM);
    solve(x3, bst, x2, y2, ansM, ansR);
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%lld", &U[i]);
    for (int i = 0; i < m; i++)
        scanf("%lld", &V[i]);
    solve(1, 1, n, m, 0, n + m - 2);
    ans[n + m - 2] = '\0';
    printf("%s\n", ans);
    return 0;
}
