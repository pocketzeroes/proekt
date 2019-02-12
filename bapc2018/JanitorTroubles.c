#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
inline double min(double a, double b){return a<b?a:b;}
inline double max(double a, double b){return a>b?a:b;}

int main(int taskJ, char**bapc){
  double a, b, c, d;
  scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
  double low  = max(abs(b-a),abs(c-d));
  double high = min(a+b, c+d);
  double mid1, mid2, area1, area2, sper1, sper2;
  do{
    mid1  = (2.0*low + high)/3.0;
    mid2  = (low + 2.0*high)/3.0;
    sper1 = (a + b + mid1)/2;
    sper2 = (c + d + mid1)/2;
    area1 = sqrt(sper1*(sper1-a)*(sper1-b)*(sper1-mid1)) + sqrt(sper2*(sper2-c)*(sper2-d)*(sper2-mid1));
    sper1 = (a + b + mid2)/2;
    sper2 = (c + d + mid2)/2;
    area2 = sqrt(sper1*(sper1-a)*(sper1-b)*(sper1-mid2)) + sqrt(sper2*(sper2-c)*(sper2-d)*(sper2-mid2));
    if(area1 > area2)
      high = mid2;
    else
      low = mid1;
  }
  while(high - low > 0.0000001);
  printf("%.8lf\n", area1);
  return 0;
}
