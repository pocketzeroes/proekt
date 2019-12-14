#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef struct{
    double x, y;
}pt;
pt newpt(double a, double b){
    return(pt){a,b};
}
int n;

double areaPolygon(pt*p){
    double area = 0.0;
    for(int i=0; i<n; i++)
        area += p[i].x * p[(i+1) % n].y - p[i].y * p[(i+1) % n].x;
    return fabs(area/2.0);
}
int main(){
    scanf("%d", &n);
    pt points[n]; clr(points);
    for(int i=0; i<n; i++){
        double x, y;
        scanf("%lf %lf", &x, &y);
        points[i] = newpt(x, y);
    }
    double targetArea;
    scanf("%lf", &targetArea);
    double area = areaPolygon(points);
    double factor = sqrt(targetArea)/sqrt(area);
    pt newPoints[n]; clr(newPoints);
    double minX = points[0].x;
    double minY = points[0].y;
    newPoints[0] = points[0];
    for(int i=1; i<n; i++){
        double nx=newPoints[i-1].x+factor*(points[i].x-points[i-1].x);
        double ny=newPoints[i-1].y+factor*(points[i].y-points[i-1].y);
        newPoints[i] = newpt(nx, ny);
        if(newPoints[i].x < minX) minX = newPoints[i].x;
        if(newPoints[i].y < minY) minY = newPoints[i].y;
    }
    for(int z=0;z<n;z++){pt point = newPoints[z];
        printf("%lf %lf\n", point.x-minX, point.y-minY);
    }
    return 0;
}
