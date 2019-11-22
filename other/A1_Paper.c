#pragma GCC optimize "-O3"
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
    int m[n-1];
    for(int i=0; i<n-1; ++i)
        scanf("%d", &m[i]);
    double res = 0;
    int    req = 1;
    double side = pow(2, -3.0/4);
    for(int i=0; req>0&&i<n-1; ++i){
        res += req * side;
        req *= 2;
        req -= m[i];
        side /= sqrt(2);
    }
    if(req > 0)
        puts("impossible");
    else
        printf("%.6lf\n", res);
    return 0;
}
