#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<float.h>


double EPSILON = 2.220446e-16;
double MAX_VALUE = DBL_MAX;
double MIN_VALUE = 2.225074e-308;

double nextUp(double x){
  if (x == -NAN)
      return -MAX_VALUE;
  if (x == NAN)
      return NAN;
  if (x == MAX_VALUE) 
      return NAN;
  double y = x * (x < 0 ? 1 - EPSILON / 2 : 1 + EPSILON);
  if (y == x) 
      y = MIN_VALUE * EPSILON > 0 ? x + MIN_VALUE * EPSILON : x + MIN_VALUE;
  if (y == NAN)
      y = +MAX_VALUE;
  double b = x + (y - x) / 2;
  if (x < b && b < y) 
      y = b;
  double c = (y + x) / 2;
  if (x < c && c < y) 
      y = c;
  return y == 0 ? -0 : y;
}
double ulp(double x){
  return x < 0.?nextUp(x)-x : x-(-nextUp(-x));
}




int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

int x;
int y;
int z;
int r;
int vx;
int vy;
int vz;
int x2;
int y2;
int z2;
int r2;
int vx2;
int vy2;
int vz2;


double fx1(double t){
    return x + vx*t;
}
double fy1(double t){
    return y + vy*t;
}
double fz1(double t){
    return z + vz*t;
}
double fx2(double t){
    return x2 + vx2*t;
}
double fy2(double t){
    return y2 + vy2*t;
}
double fz2(double t){
    return z2 + vz2*t;
}
double dist(double t){
    return sqrt(    pow(fx2(t) - fx1(t), 2) +
                    pow(fy2(t) - fy1(t), 2) +
                    pow(fz2(t) - fz1(t), 2));
}
bool isIntersecting(double t){
    double dst = dist(t);
    return (dst - (r + r2)) <= 1e-7;
}
double apply(double t){
    return dist(t);
}
double ternarySearch(double left, double right){
    while (1){
        if ((right - left) < 10 * ulp(right))
            return (left + right)/2.0;
        double leftThird  = (2*left + right)/3;
        double rightThird = (left + 2*right)/3;
        if(apply(leftThird) < apply(rightThird))
            right = rightThird; 
        else
            left = leftThird;   
    }
}
double binarySearch(double left, double right){
    while(1){
        if((right - left) < 10*ulp(right))
            return (left + right) / 2.0;
        double mid = (left + right) / 2.0;
        if(isIntersecting(mid))
            right = mid;
        else
            left = mid;
    }
}
int main(){
    int T = in_nextInt();
    for (int t = 0; t < T; t++) {
        x   = in_nextInt();
        y   = in_nextInt();
        z   = in_nextInt();
        r   = in_nextInt();
        vx  = in_nextInt();
        vy  = in_nextInt();
        vz  = in_nextInt();
        x2  = in_nextInt();
        y2  = in_nextInt();
        z2  = in_nextInt();
        r2  = in_nextInt();
        vx2 = in_nextInt();
        vy2 = in_nextInt();
        vz2 = in_nextInt();
        double closestTime = ternarySearch(0, 100000);
        if(isIntersecting(closestTime)){
            double time = binarySearch(0, closestTime);
            printf("%lf\n", time);
        }
        else
            puts("No collision");
    }
    return 0;
}
