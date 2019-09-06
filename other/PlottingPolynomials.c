#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n;
    scanf("%d", &n);
    int coeff[n + 1];
    for(int i = n; i >= 0; --i){
        scanf("%d", &coeff[i]);
    }
    int c[n + 1];
    for (int i = 0; i <= n; ++i) {
        c[i] = 0;
        int pow_i = 1;
        for (int j = 0; j <= n; ++j) {
            c[i] += pow_i * coeff[j];
            pow_i *= i;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = n; j > i; --j) {
            c[j] -= c[j - 1];
        }
    }
    for (int i = 0; i <= n; ++i) {
        if(i)
            printf(" ");
        printf("%d", c[i]);
    }
    puts("");
    return 0;
}
