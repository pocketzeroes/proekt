#include<stdio.h>

int ans[] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 4};

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", ans[(n-1) % 10] );
    return 0;
}
