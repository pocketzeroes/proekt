#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  double sx, sy, fx, fy;
  scanf("%lf %lf %lf %lf", &sx, &sy, &fx, &fy);
  int n;
  scanf("%d", &n);
  double v[n],
         y[n];
  for(int i=0; i<n-1; ++i)
    scanf("%lf", &y[i]);
  y[n-1] = fy;
  for(int i=0; i<n; ++i)
    scanf("%lf", &v[i]);
  for(int i=n-1; i>0; --i)
    y[i] -=y [i-1];
  y[0] -= sy;
  double x = fabs(sx - fx);
  double mxs0=1;
  for(int i=0; i<n; ++i)
    mxs0 = fmin(mxs0, v[0]/v[i]);
  double a=0,
         b=mxs0;
  double t;
  for(int it=0; it<100; ++it){
    double tx=0;
    t=0;
    double s0=(a+b)/2;
    for(int i=0;i<n;++i){
      double s=s0*v[i]/v[0];
      double c=sqrt(1-s*s);
      double h=y[i]/c;
      double dx=h*s;
      double dt=h/v[i];
      tx+=dx;
      t +=dt;
    }
    if(tx<x)
      a=s0;
    else
      b=s0;
  }
  printf("%.10f\n", t);
  return 0;
}
