#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int answer = 0, reminder = 0;
    while (n) {
        answer += n;
        n += reminder;
        reminder = n % k;
        n /= k;
    }
    printf("%d", answer);
    return 0;
}
