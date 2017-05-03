#include <stdio.h>

int main() {
    int a;
    scanf("%d", &a);
    printf("%d", __builtin_popcount(a));
    return 0;
}

