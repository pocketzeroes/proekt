#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

const double EPS = 1e-12;
double naive_answer;
double x,y,w,v;
double r,R;
double phi;
double PI;
double TAU;


double sgn(double x){
  return x < 0 ? -1 : 1;
}
double g(double theta){
  double X = r * cos(theta - TAU);
  double Y = r * sin(theta - TAU) + r;
  if(hypot(X,Y) > R)
    return naive_answer;
  double a = fabs(Y - r), 
         b = fabs(X);
  if(atan2(Y-r,X) > 0)
    a = -a;
  if(X < 0)
    b = -b;
  double tA = a*a*(R*R-Y*Y) + 2*a*b*X*Y + b*b*(R*R-X*X);
  double tB = a * X + b * Y;
  double tC = a*a + b*b;
  double t  = max((-sqrt(tA) - tB) / tC,(sqrt(tA) - tB) / tC);
  double Xp = X + a*t, 
         Yp = Y + b*t;
  double phi_p = atan2(Yp,Xp);
  if(phi_p < 0)
    phi_p += 2*PI;
  if(phi_p - phi > EPS)
    return naive_answer;
  return (phi - phi_p) / w + (hypot(Xp-X,Yp-Y) + r * theta) / v;
}
double f(double lo, double hi){
  double q1 = (2*lo + hi)/3, 
         q2 = (lo + 2*hi)/3;
  double a = g(q1), 
         b = g(q2);
  if(fabs(lo-hi) < EPS && 
     fabs(a-b)   < EPS)
    return (a+b)/2;
  return a > b ? f(q1,hi) : 
                 f(lo,q2);
}
int main(){
  PI = acos(-1.0);
  TAU = 0.5*PI;
  scanf("%lf %lf %lf %lf", &x, &y, &v, &w);
  y = fabs(y);
  r = v / w;
  R   = hypot(x, y);
  phi = atan2(y, x);
  naive_answer = g(0);
  printf("%.8lf\n", min(f(0,TAU), f(TAU,PI)) );
  return 0;
}
