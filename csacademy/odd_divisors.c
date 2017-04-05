#include <stdio.h>

inline long long sqr(long long n) { return n * n;}

long long count(long long n) {
    if (n == 0) return 0;
    if (n % 2) {
        return sqr((n + 1) / 2) + count(n / 2);
    } else {
        return sqr(n / 2) + count(n / 2);
    }
}
int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%lld", count(b) - count(a - 1));
    }
}


