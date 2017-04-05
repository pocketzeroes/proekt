#include <math.h>
#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    int res = 0;
    for (int i = a; i <= b; ++i) {
        int divCount = 0;
        for (int j = 1; j <= i; ++j) {
            if (i % j == 0) {
                ++divCount;
            }
        }
        if (divCount % 2) {
            ++res;
        }
    }
    printf("%d", res);
}
