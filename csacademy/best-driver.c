#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int x1, x2, c1, c2;
    int t;
    double ans;
    scanf("%d", &t);
    while(t--){
        scanf("%d %d %d %d", &x1, &x2, &c1, &c2);
        ans = (c2 * (x1 + x2) - c1 * x1) / (double) x2;
        printf("%.7lf\n", ans);
    }
    return 0;
}
