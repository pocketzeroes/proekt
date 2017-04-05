#include <stdio.h>

int jeans [1005];
int shirts[1005];

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", jeans + i);
    }
    for (int i = 1; i <= m; ++ i) {
        scanf("%d", shirts + i);
    }
    int answer = 0;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            if (abs(jeans[i] - shirts[j]) >= k) {
                ++answer;
            }
        }
    }
    printf("%d", answer);
    return 0;
}
