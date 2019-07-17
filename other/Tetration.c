#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    double n;
    scanf("%lf", &n);
    printf("%.6lf\n", pow(n, (1./n)));
    return 0;
}
