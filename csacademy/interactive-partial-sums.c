#include <stdio.h>
#include <stdint.h>
#define int long long

int32_t main() {
    int n, partial_sum = 0, number, i;
    scanf("%lld", &n);
    for (i = 1; i <= n; i += 1) {
        scanf("%lld", &number);
        partial_sum += number;
        printf("%lld\n", partial_sum);
        fflush(stdout);
    }
    return 0;
}
