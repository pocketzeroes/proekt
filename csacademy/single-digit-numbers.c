#include <stdio.h>
#include<stdbool.h>

int main() {
    int a, b; 
    scanf("%d %d", &a, &b);
    int result = 0;
    for (int i = a; i <= b; i ++) {
        int x = i;
        int ch = x % 10;
        bool ok = true;
        while (x) {
            if (x % 10 != ch) {
                ok = false;
            }
            x /= 10;
        }
        if (ok) {
            result ++;
        }
    }
    printf("%d\n", result);
}
