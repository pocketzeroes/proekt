#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}

#define mp newPair
typedef struct{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
typedef long long ll;
typedef pair pii;

enum{ N = 505};
int MOD;

int add(int x, int y) {
    x += y;
    if (x >= MOD) 
        return x - MOD;
    return x;
}
int sub(int x, int y) {
    x -= y;
    if (x < 0) 
        return x + MOD;
    return x;
}
int mult(int x, int y) {
    return ((ll)x * y) % MOD;
}

int C[N][N];
int ans[N];
int dp[N];
int n;

int main() {
    scanf("%d%d", &n, &MOD);
    for (int i = 0; i < N; i++)
        C[i][0] = C[i][i] = 1;
    for (int i = 1; i < N; i++)
        for (int j = 1; j < i; j++)
            C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
    if (n & 1) {
        for (int i = 0; i < n; i++)
            printf("0\n");
        return 0;
    }
    n /= 2;
    for (int m = 1; m <= 2 * n; m++) {
        dp[0] = 1;
        for (int x = 1; x <= n; x++) {
            dp[x] = 0;
            for (int y = 0; y <= min(m / 2, x); y++) {
                int z = x - y;
                if (z & 1) continue;
                z /= 2;
                dp[x] = add(dp[x], mult(dp[z], C[m][2 * y]));
            }
        }
        ans[m] = dp[n];
    }
    for (int i = 1; i <= 2 * n; i++)
        for (int j = 1; j < i; j++)
            ans[i] = sub(ans[i], mult(C[i][j], ans[j]));
    for (int i = 1; i <= 2 * n; i++)
        printf("%d\n", ans[i]);
    return 0;
}
