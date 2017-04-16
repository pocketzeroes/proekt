#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main() {
    int k;
    scanf("%d", &k);
    int num_ok = 0;
    for (int i = 1;; i += 1) {
        bool ok = true;
        for (int p = 20; p >= 0; p -= 1) {
            if ((i & (1 << p)) && i & (1 << (p + 1))) {
                ok = false;
            }
        }
        if (ok) {
            num_ok += 1;
        }
        if (num_ok == k) {
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}
