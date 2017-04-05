#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int signs[n - 1];//, trimmedSigns;
    int trimmedSigns[n-1];
    int trimmedSignsSz=0;
    for (int i = 0; i < n - 1; ++ i) {
        scanf("%d", signs + i );
        if (signs[i]) {
            trimmedSigns[trimmedSignsSz++] = signs[i];
        }
    }
    int m = trimmedSignsSz;
    int digits[m + 1];
    digits[0] = 9;
    for (int i = 1; i <= m; ++ i) {
        if (trimmedSigns[i - 1] == 1) {
            digits[i] = digits[i - 1] - 1;
            if (digits[i] == -1) {
                printf( "-1\n");
                return 0;
            }
        } 
        else {
            digits[i] = 9;
            for (int j = i - 1; j >= 0 && digits[j] == digits[j + 1]; -- j) {
                digits[j] -= 1;
                if (digits[j] == -1 || (digits[j] == 0 && j == 0)) {
                    printf( "-1\n");
                    return 0;
                }
            }
        }
    }
    int pos = 0;
    for (int i = 0; i <= m; ++ i) {
        printf("%d", digits[i]);
        while (pos < n - 1 && signs[pos] == 0) {
            printf("%d", digits[i]);
            ++pos;
        }
        ++pos;
    }
    return 0;
}
