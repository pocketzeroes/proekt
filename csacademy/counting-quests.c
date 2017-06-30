#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include <ctype.h>

enum{ SIZE = 1 << 17};
char buffer[SIZE];
int pointer = SIZE;
enum{ MAXN = 300};
int dp[1 + MAXN], sum[1 + MAXN][1 + MAXN], combinations[1 + 2 * MAXN][1 + 2 * MAXN], ways[1 + MAXN];

char Advance() {
    if (pointer == SIZE) {
        fread(buffer, 1, SIZE, stdin);
        pointer = 0;
    }
    return buffer[pointer++];
}
int Read() {
    int answer = 0;
    char ch = Advance();
    while (!isdigit(ch))
        ch = Advance();
    while (isdigit(ch)) {
        answer = answer * 10 + ch - '0';
        ch = Advance();
    }
    return answer;
}
int RaiseToPower(int base, int power, int mod) {
    int answer = 1;
    while (power) {
        if (power % 2)
            answer = (1LL * answer * base) % mod;
        base = (1LL * base * base) % mod;
        power /= 2;
    }
    return answer;
}
void Precompute(int n, int mod) {
    for (int i = 0; i <= n; i++)
        ways[i] = RaiseToPower(2, i * (i + 1) / 2, mod);
    sum[0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int j = 2 * i; j <= n; j++)
            for (int k = 2; k + j <= n; k++)
                sum[i + 1][j + k] = (1LL * sum[i][j] * ways[k - 2] + sum[i + 1][j + k]) % mod;
    combinations[0][0] = 1;
    for (int i = 1; i <= 2 * n; i++) {
        combinations[i][0] = 1;
        for (int j = 1; j <= i; j++)
            combinations[i][j] = (combinations[i - 1][j - 1] + combinations[i - 1][j]) % mod;
    }
}

int main() {
    int n, mod;
    scanf("%d%d", &n, &mod);
    Precompute(n, mod);
    for (int i = 1; i <= n; i++) {
        dp[i] = ways[i];
        for (int j = 1; j <= i; j++)
            for (int k = 2 * j; k <= i; k++) {
                int subtract = (1LL * sum[j][k] * dp[i - k + j]) % mod;
                dp[i] = (-(1LL * subtract * combinations[i - k + j][j] % mod) + dp[i] + mod) % mod;
            }
    }
    printf("%d\n", dp[n]);
    return 0;
}


























