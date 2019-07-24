#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

long double d, s;

int main() {
    scanf("%Lf%Lf", &d, &s);
    long double a_min = 0;
    long double a_max = 1e8;
    while (a_max - a_min > 1e-12){
        long double a = (a_max + a_min) / 2;
        long double v = a * cosh(d / (2 * a)) - a - s;
        if (v > 0)
            a_min = a;
        else
            a_max = a;
    }
    printf("%.15Lf\n", 2*a_min*sinh(d / (2 * a_min)) );
    return 0;
}
