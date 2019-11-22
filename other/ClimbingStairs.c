#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int N, R, O;
    scanf("%d %d %d", &N, &R, &O);
    int before_office = fmax(R, N + (N-R) % 2) + abs(R - O) + O;
    int after_office = O + fmax(abs(R - O), N-O + (N-R) % 2) + R;
    printf("%d\n", (int)fmin(before_office, after_office));
    return 0;
}
