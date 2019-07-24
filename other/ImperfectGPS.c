#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define sqr(x) ((x) * (x))
int n, t;

int main(){
    scanf("%d%d", &n, &t);
    double x0, y0; int tt0;
    double s = 0;
    double gps_s = 0;
    scanf("%lf %lf %d", &x0, &y0, &tt0);
    double xg, yg;
    xg = x0;
    yg = y0;
    for(int i = 1; i < n; ++i){
        double x, y; int tt;
        scanf("%lf %lf %d", &x, &y, &tt);
        s += sqrt(sqr(x - x0) + sqr(y - y0));
        double dx = (x - x0) / (tt - tt0);
        double dy = (y - y0) / (tt - tt0);
        for (; tt0 < tt; ++tt0){
            if (tt0 % t == 0){
                gps_s += sqrt(sqr(x0 - xg) + sqr(y0 - yg));
                xg = x0;
                yg = y0;
            }
            x0 += dx;
            y0 += dy;
        }
    }
    if (xg != x0 || yg != y0) {
        gps_s += sqrt(sqr(xg - x0) + sqr(yg - y0));
    }
    printf("%lf\n", 100.*fabs(gps_s - s)/s);
    return 0;
}
