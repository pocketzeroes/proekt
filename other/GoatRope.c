#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

double dist(double x1, double y1, double x2, double y2){
    return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}
int main(){
    int x, y, x1, y1, x2, y2;
    scanf("%d %d %d %d %d %d", &x, &y, &x1, &y1, &x2, &y2);
    double mindist = dist(x, y, x1, y1);
    mindist = fmin(mindist, dist(x, y, x2, y1));
    mindist = fmin(mindist, dist(x, y, x1, y2));
    mindist = fmin(mindist, dist(x, y, x2, y2));
    if(x1 <= x && x <= x2){
        mindist = fmin(mindist, fabs(y-y1));
        mindist = fmin(mindist, fabs(y-y2));
    }
    if(y1 <= y && y <= y2){
        mindist = fmin(mindist, fabs(x-x1));
        mindist = fmin(mindist, fabs(x-x2));
    }
    printf("%.30lf\n", mindist);
    return 0;
}
