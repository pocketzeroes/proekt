#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main() {
    int n;
    scanf("%d", &n);
    double t, p, mn = 1.1;
    int type = 0;
    for (int i = 1 ; i <= n ; ++i) {
        scanf("%lf %lf", &t, &p);
        if (mn > p / t) {
            mn = p / t;
            type = i;
        }
    }
    printf("%d\n", type);
    return 0;
}
