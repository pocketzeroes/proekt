#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

long xc, yc, sc, ri, rf, xp, yp, sp, d;

int main(){
    scanf("%ld%ld%ld%ld%ld%ld%ld%ld", &xc, &yc, &sc, &ri, &rf, &xp, &yp, &sp);
    d = sqrt((xp-xc)*(xp-xc)+(yp-yc)*(yp-yc));
    if(d <= rf || (d <= ri && sp >= sc))
        puts("0.0");
    else if(d < ri){
        double dt = (ri - d)/(double)(sc - sp),
               ft = (d - rf)/(double) sp;
        printf("%.9lf\n", (ft < dt) ? (double)ft : (double) ft - dt);
    }
    else if(sp <= sc)
        printf("%.9lf\n", (d - rf) / (double) sp);
    else{
        double dt = (d - ri)/(double)(sp-sc),
               ft = (d - rf)/(double) sp;
        printf("%.9lf\n", (ft <= dt) ? (double) ft : (double) dt);
    }
    return 0;
}
