#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i += 2) {
        printf("%d %d\n", i , i + 1);
        for (int j = 3; j < i; j += 1) {
            printf("%d %d\n", i , j);
        }
        if (i != 1) {
            if (i != 3) {
                printf("%d %d\n", i , i + 1);
            }
            printf("1 %d\n", i    );
            printf("2 %d\n", i + 1);
            for (int j = 3; j < i - j + 2; j += 1) {
                printf("%d %d\n", j , i - j + 2);
            }
        }
    }
    return 0;
}
