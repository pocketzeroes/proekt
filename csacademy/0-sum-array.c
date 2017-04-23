#include<stdio.h>

enum{ kMaxN = 1005};

int el[kMaxN];

int main() {
    int n;
    scanf("%d", &n);
    int sum = 0;
    for (int i = 1; i <= n; i += 1) {
        scanf("%d", &el[i]);
        sum += el[i];
    }
    int answer = -1;
    for (int i = 1; i <= n; i += 1) {
        if (2 * el[i] == sum) {
            answer = i;
            break;
        }
    }
    printf("%d\n", answer);
    return 0;
}
