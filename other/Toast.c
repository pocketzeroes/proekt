#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int N, T;
double D;
int main(){
    scanf("%d %lf %d", &N, &D, &T);
    if(T % N || (T / N) >= N/2){
        printf("0 %lf\n", D);
        return 0;
    }
    T /= N;
    double R1 = sqrt(2) * D / sqrt(1 - cos(2*M_PI*(T+1)/N));
    double R2 = sqrt(2) * D / sqrt(1 - cos(2*M_PI*T/N));
    printf("%lf %lf\n", R1, R2);
    return 0;
}
