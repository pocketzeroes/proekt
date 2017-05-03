#include <stdio.h>


int main() {
    unsigned n;
    scanf("%d", &n);
    unsigned p = 1;
    while ((p << 1) <= n) {
        p <<= 1;
    }
    printf("%d\n", ((n ^ p) << 1) + 1);
    return 0;
}

