#include <stdio.h>


enum{ MAX_N = 100000};
const int MAX_VAL = (int)1e9;
const int MOD = (int)1e9 + 7;
int n, a, b;
int v[MAX_N + 1];
int s[MAX_N + 1];

void read() {
    scanf("%d %d %d", &n, &a, &b);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &v[i]);
    }
}
int main() {
    read();
    long long ans = 0;
    for (int bit = 0; bit < 30; ++bit) {
        int count[] = {0, 0};
        for (int i = 1; i <= n; ++i) {
            s[i] = s[i - 1] ^ ((v[i] >> bit) & 1);
            if (i - b > 0) {
                count[s[i - b - 1]] -= 1;
            }
            if (i - a >= 0) {
                count[s[i - a]] += 1;
            }
            ans += (long long)count[1 ^ s[i]] * (1 << bit);
            if (ans >= MOD) {
                ans %= MOD;
            }
        }
    }
    printf("%lld\n", ans);
}
