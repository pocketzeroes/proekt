#include<stdio.h>
int sum(int A, int B) {
    return A+B;
}

int main() {
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; ++i) {
        int A, B;
        scanf("%d %d", &A, &B);
        printf("%d\n", sum(A, B));
    }
    return 0;
}
