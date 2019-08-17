#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

double circle_segment(double rad, double th) {
  return rad*rad*(th - sin(th))/2;
}
int main(){
  int n;
  scanf("%d", &n);
  int prob=1;
  for(int i=0;i<n;i++){
    double f, R, t, r, g;
    scanf("%lf%lf%lf%lf%lf", &f, &R, &t, &r, &g);
    double rad = R-t-f;
    double ar = 0.0;
    for (double x1 = r+f; x1 < R-t-f; x1 += g+2*r){
      for (double y1 = r+f; y1 < R-t-f; y1 += g+2*r) {
        double x2 = x1 + g - 2*f;
        double y2 = y1 + g - 2*f;
        if (x2 <= x1 || y2 <= y1)
          continue;
        if (x1*x1 + y1*y1 >= rad*rad)
          continue;
        if (x2*x2 + y2*y2 <= rad*rad)
          ar += (x2-x1)*(y2-y1);
        else if (x1*x1 + y2*y2 >= rad*rad && x2*x2 + y1*y1 >= rad*rad)
          ar += circle_segment(rad, acos(x1/rad) - asin(y1/rad)) + (sqrt(rad*rad - x1*x1)-y1) * (sqrt(rad*rad - y1*y1)-x1) / 2;
        else if (x1*x1 + y2*y2 >= rad*rad)
          ar += circle_segment(rad, acos(x1/rad) - acos(x2/rad)) + (x2-x1) * (sqrt(rad*rad - x1*x1)-y1 + sqrt(rad*rad - x2*x2)-y1) / 2;
        else if (x2*x2 + y1*y1 >= rad*rad)
          ar += circle_segment(rad, asin(y2/rad) - asin(y1/rad)) + (y2-y1) * (sqrt(rad*rad - y1*y1)-x1 + sqrt(rad*rad - y2*y2)-x1) / 2;
        else
          ar += circle_segment(rad, asin(y2/rad) - acos(x2/rad)) + (x2-x1)*(y2-y1) - (y2-sqrt(rad*rad - x2*x2)) * (x2-sqrt(rad*rad - y2*y2)) / 2;
      }
    }
    printf("Case #%d: %.9lf\n", prob++, 1.0 - ar / (M_PI*R*R/4));
  }
  return 0;
}
