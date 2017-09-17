#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int main() {
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);
    for (int i = 0; i < n; i++) {
        int c;
        scanf("%d", &c);
        a += c;
    }
    for (int i = 0; i < n; i++) {
        int c;
        scanf("%d", &c);
        b += c;
    }
    if (a > b) {
        puts("1");
    }
    else if (b > a) {
        puts("2");
    }
    else {
        puts("0");
    }
}
