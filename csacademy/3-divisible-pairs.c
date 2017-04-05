#include <stdio.h>
#include<stdint.h>

int64_t n;
long long freq[3];

int main() {
    scanf("%lld", &n);
    for (int64_t i = 0; i < n; ++i) {
        int64_t val;
        scanf("%lld", &val);
        freq[val % 3] += 1;
    }
    printf("%lld", freq[0] * (freq[0] - 1) / 2 + freq[1] * freq[2] );
}
