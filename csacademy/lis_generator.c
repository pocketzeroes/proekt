#include <stdio.h>

int main() {
    int K; 
    scanf("%d", &K);
    int maxBit = 0;
    for (int i = 0; i < 30; i += 1) {
        if (K & (1 << i)) {
            maxBit = i;
        }
    }
    for (int i = 0; i <= maxBit; i += 1) {
        if ((K & (1 << i)) == 0) {
            printf("%d ", maxBit + 2 + i );
        }
        if (i == 0) {
            printf("%d ", i + 1 );
        } 
        else {
            printf("%d %d ", i + 1 , i + 1 );
        }
        if (K & (1 << i)) {
            printf("%d ", maxBit + 2 + i );
        }
    }
    return 0;
}
