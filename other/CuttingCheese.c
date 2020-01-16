#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define EPS 1e-8

double slice(double R, double z, double h){
  h = fmax(0.0, fmin(2*R, h-(z-R)));
  return M_PI*h*h*(R-h/3);
}

int main(){
  int N, S;
  while(scanf("%d %d", &N, &S)==2){
    double vol = 1e15;
    double vr[N];
    double vx[N];
    double vy[N];
    double vz[N];
    for(int i=0; i<N; i++){
      scanf("%lf %lf %lf %lf", &vr[i], &vx[i], &vy[i], &vz[i]);
      vol -= 4.0/3.0*M_PI*vr[i]*vr[i]*vr[i];
    }
    double last = 0.0;
    for(int i = 0; i < S; i++){
      double goal = vol*(i+1)/S;
      double lo = last,
             hi = 100000.0;
      while (hi-lo > EPS){
        double h   = (hi+lo)/2,
               cur = h*1e10;
        for(int i=0; i<N; i++)
          cur -= slice(vr[i], vz[i], h);
        if(cur>goal)
          hi = h;
        else
          lo = h;
      }
      double h = (hi+lo)/2;
      printf("%.9lf\n", (h-last)/1000);
      last = h;
    }
  }
  return 0;
}
