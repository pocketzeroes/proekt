#include <stdio.h>

enum{ MAX_N = 50000};
int n;
int v[MAX_N];

void read() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &v[i]);
    }
}
int main() {
    read();
    int ans = 0;
    int zeroCount = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (v[i] == 0) {
            zeroCount += 1;
        }
        if (v[i] == 1) {
            ans += zeroCount;
        }
    }
    printf("%d", ans);
}
